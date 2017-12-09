

#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2017 <+YOU OR YOUR COMPANY+>.
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#
import numpy
from gnuradio import gr
from gnuradio import digital
import ofdm_allocator_swig as ofdm_allocator
# from utils import tagged_streams

try:
    # This will work when feature #505 is added.
    from gnuradio import fft
    from gnuradio import blocks
    from gnuradio import analog
except ImportError:
    # Until then this will work.
    import fft_swig as fft
    import blocks_swig as blocks
    import analog_swig as analog

_def_fft_len = 64
_def_cp_len = 16
_def_frame_length_tag_key = "frame_length"
_def_packet_length_tag_key = "packet_length"
_def_packet_num_tag_key = "packet_num"
# Data and pilot carriers are same as in 802.11a
_def_occupied_carriers = (range(-26, -21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22, 27),)
vector_0 = (range(-26, -21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22, 27))
_def_pilot_carriers=((-21, -7, 7, 21,),)
_pilot_sym_scramble_seq = (
        1,1,1,1, -1,-1,-1,1, -1,-1,-1,-1, 1,1,-1,1, -1,-1,1,1, -1,1,1,-1, 1,1,1,1, 1,1,-1,1,
        1,1,-1,1, 1,-1,-1,1, 1,1,-1,1, -1,-1,-1,1, -1,1,-1,-1, 1,-1,-1,1, 1,1,1,1, -1,-1,1,1,
        -1,-1,1,-1, 1,-1,1,1, -1,-1,-1,1, 1,-1,-1,-1, -1,1,-1,-1, 1,-1,1,1, 1,1,-1,1, -1,1,-1,1,
        -1,-1,-1,-1, -1,1,-1,1, 1,-1,1,-1, 1,1,1,-1, -1,1,-1,-1, -1,1,1,1, -1,-1,-1,-1, -1,-1,-1
)
_def_pilot_symbols= tuple([(x, x, x, -x) for x in _pilot_sym_scramble_seq])
_seq_seed = 42


def _get_active_carriers(fft_len, occupied_carriers, pilot_carriers):
    """ Returns a list of all carriers that at some point carry data or pilots. """
    active_carriers = list()
    for carrier in list(occupied_carriers[0]) + list(pilot_carriers[0]):
        if carrier < 0:
            carrier += fft_len
        active_carriers.append(carrier)
    return active_carriers

def _make_sync_word1(fft_len, occupied_carriers, pilot_carriers):
    """ Creates a random sync sequence for fine frequency offset and timing
    estimation. This is the first of typically two sync preamble symbols
    for the Schmidl & Cox sync algorithm.
    The relevant feature of this symbols is that every second sub-carrier
    is zero. In the time domain, this results in two identical halves of
    the OFDM symbols.
    Symbols are always BPSK symbols. Carriers are scaled by sqrt(2) to keep
    total energy constant.
    Carrier 0 (DC carrier) is always zero. If used, carrier 1 is non-zero.
    This means the sync algorithm has to check on odd carriers!
    """
    active_carriers = _get_active_carriers(fft_len, occupied_carriers, pilot_carriers)
    numpy.random.seed(_seq_seed)
    bpsk = {0: numpy.sqrt(2), 1: -numpy.sqrt(2)}
    sw1 = [bpsk[numpy.random.randint(2)]  if x in active_carriers and x % 2 else 0 for x in range(fft_len)]
    return numpy.fft.fftshift(sw1)

def _make_sync_word2(fft_len, occupied_carriers, pilot_carriers):
    """ Creates a random sync sequence for coarse frequency offset and channel
    estimation. This is the second of typically two sync preamble symbols
    for the Schmidl & Cox sync algorithm.
    Symbols are always BPSK symbols.
    """
    active_carriers = _get_active_carriers(fft_len, occupied_carriers, pilot_carriers)
    numpy.random.seed(_seq_seed)
    bpsk = {0: 1, 1: -1}
    sw2 = [bpsk[numpy.random.randint(2)] if x in active_carriers else 0 for x in range(fft_len)]
    sw2[0] = 0j
    return numpy.fft.fftshift(sw2)

def _get_constellation(bps):
    """ Returns a modulator block for a given number of bits per symbol """
    constellation = {
            1: digital.constellation_bpsk(),
            2: digital.constellation_qpsk(),
            3: digital.constellation_8psk()
    }
    try:
        return constellation[bps]
    except KeyError:
        print 'Modulation not supported.'
        exit(1)

class ofdm_tx(gr.hier_block2):
    """
    docstring for block ofdm_tx
    """
    def __init__(self, fft_len=_def_fft_len, cp_len=_def_cp_len,
                 packet_length_tag_key=_def_packet_length_tag_key,
                 pilot_carriers=_def_pilot_carriers,
                 pilot_symbols=_def_pilot_symbols,
                 max_len_data_subcarr=48,
                 max_len_pilot_subcarr=4,
                 max_vector_data_subcarr=10,
                 max_vector_pilot_subcarr=1,
                 fixed_data=True,
                 fixed_pilot=True,
                 bps_header=1,
                 bps_payload=1,
                 sync_word1=None,
                 sync_word2=None,
                 rolloff=0,
                 debug_log=False,
                 scramble_bits=False
                 ):
        gr.hier_block2.__init__(self,
            "ofdm_tx",
                    gr.io_signature2(2, 2, gr.sizeof_char, gr.sizeof_int),
                    gr.io_signature(1, 1, gr.sizeof_gr_complex))

        ### Param init / sanity check ########################################
        self.fft_len           = fft_len
        self.cp_len            = cp_len
        self.packet_length_tag_key = packet_length_tag_key
        self.pilot_carriers    = pilot_carriers
        self.pilot_symbols     = pilot_symbols
        self.bps_header        = bps_header
        self.bps_payload       = bps_payload
        self.sync_word1        = sync_word1
        self.max_len_data_subcarr = max_len_data_subcarr
        self.max_len_pilot_subcarr = max_len_pilot_subcarr
        self.max_vector_data_subcarr = max_vector_data_subcarr
        self.max_vector_pilot_subcarr = max_vector_pilot_subcarr
        self.fixed_data = fixed_data
        self.fixed_pilot = fixed_pilot

        if sync_word1 is None:
            self.sync_word1 = _make_sync_word1(fft_len, (vector_0,), pilot_carriers)
        else:
            if len(sync_word1) != self.fft_len:
                raise ValueError("Length of sync sequence(s) must be FFT length.")
        self.sync_words = [self.sync_word1,]
        if sync_word2 is None:
            self.sync_word2 = _make_sync_word2(fft_len, (vector_0,), pilot_carriers)
        else:
            self.sync_word2 = sync_word2
        if len(self.sync_word2):
            if len(self.sync_word2) != fft_len:
                raise ValueError("Length of sync sequence(s) must be FFT length.")
            self.sync_word2 = list(self.sync_word2)
            self.sync_words.append(self.sync_word2)
        if scramble_bits:
            self.scramble_seed = 0x7f
        else:
            self.scramble_seed = 0x00 # We deactivate the scrambler by init'ing it with zeros
        ### Header modulation ################################################
        crc = digital.crc32_bb(False, self.packet_length_tag_key)
        header_constellation  = _get_constellation(bps_header)
        header_mod = digital.chunks_to_symbols_bc(header_constellation.points())

        # formatter_object = digital.packet_header_ofdm(
        #     occupied_carriers=(vector_0,), n_syms=1,
        #     bits_per_header_sym=self.bps_header,
        #     bits_per_payload_sym=self.bps_payload,
        #     scramble_header=scramble_bits
        # )

        formatter_object = ofdm_allocator.packet_header_ofdm_alix(
            occupied_carriers=(vector_0,), n_syms=1,
            bits_per_header_sym=self.bps_header,
            bits_per_payload_sym=self.bps_payload,
            scramble_header=scramble_bits
        )

        # header_gen = digital.packet_headergenerator_bb(formatter_object.base(), self.packet_length_tag_key)
        header_gen = ofdm_allocator.packet_header_gen(formatter_object.base(), self.max_len_data_subcarr, self.max_len_pilot_subcarr, self.max_vector_data_subcarr, self.max_vector_pilot_subcarr, self.fixed_pilot, 1, self.packet_length_tag_key)
        header_payload_mux = blocks.tagged_stream_mux(
                itemsize=gr.sizeof_gr_complex*1,
                lengthtagname=self.packet_length_tag_key,
                tag_preserve_head_pos=1 # Head tags on the payload stream stay on the head
        )
        self.connect(
                (self,0),
                crc,
                (header_gen,0),
                header_mod,
                (header_payload_mux, 0)
        )
        if debug_log:
            self.connect(header_gen, blocks.file_sink(1, 'tx-hdr.dat'))
        ### Payload modulation ###############################################
        payload_constellation = _get_constellation(bps_payload)
        payload_mod = digital.chunks_to_symbols_bc(payload_constellation.points())
        payload_scrambler = digital.additive_scrambler_bb(
            0x8a,
            self.scramble_seed,
            7,
            0, # Don't reset after fixed length (let the reset tag do that)
            bits_per_byte=8, # This is before unpacking
            reset_tag_key=self.packet_length_tag_key
        )
        payload_unpack = blocks.repack_bits_bb(
            8, # Unpack 8 bits per byte
            bps_payload,
            self.packet_length_tag_key
        )
        self.connect(
            crc,
            payload_scrambler,
            payload_unpack,
            payload_mod,
            (header_payload_mux, 1)
        )
        ### Create OFDM frame ################################################
        # vector_subcarrier = ofdm_allocator.vector_source_tagged(vector_0,True,1,self.packet_length_tag_key,())

        allocator = ofdm_allocator.allocator_subcarrier(
            self.fft_len,
            vector_len=1,
            fixed_data = self.fixed_data,
            fixed_pilot = self.fixed_pilot,
            max_len_data_subcarr = self.max_len_data_subcarr,
            max_len_pilot_subcarr = self.max_len_pilot_subcarr,
            max_vector_data_subcarr = self.max_vector_data_subcarr,
            max_vector_pilot_subcarr = self.max_vector_pilot_subcarr,
            pilot_carriers=self.pilot_carriers,
            pilot_symbols=self.pilot_symbols,
            sync_words=self.sync_words,
            len_tag_key=self.packet_length_tag_key,
            output_is_shifted = True
        )
        ffter = fft.fft_vcc(
                self.fft_len,
                False, # Inverse FFT
                (), # No window
                True # Shift
        )
        cyclic_prefixer = digital.ofdm_cyclic_prefixer(
            self.fft_len,
            self.fft_len+self.cp_len,
            rolloff,
            self.packet_length_tag_key
        )
        self.connect((self,1), (allocator,1))
        self.connect((self,1), (header_gen,1))
        self.connect(header_payload_mux, (allocator,0), ffter, cyclic_prefixer, self)
        if debug_log:
            self.connect(allocator,       blocks.file_sink(gr.sizeof_gr_complex * fft_len, 'tx-post-allocator.dat'))
            self.connect(cyclic_prefixer, blocks.file_sink(gr.sizeof_gr_complex,           'tx-signal.dat'))
            # # Define blocks and connect them
            # self.connect()
