#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: OFDM Rx
# Description: Example of an OFDM receiver
# Generated: Thu Dec  7 11:06:37 2017
##################################################

from gnuradio import analog
from gnuradio import blocks
from gnuradio import channels
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import fft
from gnuradio import gr
from gnuradio.digital.utils import tagged_streams
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from optparse import OptionParser
import numpy
import ofdm_allocator
import pmt


class rx_ofdm(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "OFDM Rx")

        ##################################################
        # Variables
        ##################################################
        self.pilot_symbols = pilot_symbols = ((1, 1, 1, -1,),)
        self.pilot_carriers = pilot_carriers = ((-21, -7, 7, 21,),)
        self.payload_mod_2 = payload_mod_2 = digital.constellation_qpsk()
        self.payload_mod = payload_mod = ofdm_allocator.constellation_qpsk()
        self.packet_length_tag_key = packet_length_tag_key = "packet_len"
        self.occupied_carriers = occupied_carriers = (range(-26, -21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22, 27),)
        self.length_tag_key = length_tag_key = "frame_len"
        self.header_mod = header_mod = ofdm_allocator.constellation_bpsk()
        self.fft_len = fft_len = 64
        self.variable_0 = variable_0 = (range(-26, -21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22, 27))
        self.sync_word2 = sync_word2 = [0j, 0j, 0j, 0j, 0j, 0j, (-1+0j), (-1+0j), (-1+0j), (-1+0j), (1+0j), (1+0j), (-1+0j), (-1+0j), (-1+0j), (1+0j), (-1+0j), (1+0j), (1+0j), (1 +0j), (1+0j), (1+0j), (-1+0j), (-1+0j), (-1+0j), (-1+0j), (-1+0j), (1+0j), (-1+0j), (-1+0j), (1+0j), (-1+0j), 0j, (1+0j), (-1+0j), (1+0j), (1+0j), (1+0j), (-1+0j), (1+0j), (1+0j), (1+0j), (-1+0j), (1+0j), (1+0j), (1+0j), (1+0j), (-1+0j), (1+0j), (-1+0j), (-1+0j), (-1+0j), (1+0j), (-1+0j), (1+0j), (-1+0j), (-1+0j), (-1+0j), (-1+0j), 0j, 0j, 0j, 0j, 0j]
        self.sync_word1 = sync_word1 = [0., 0., 0., 0., 0., 0., 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 0., 0., 0., 0., 0.]
        self.samp_rate = samp_rate = 10000
        self.payload_equalizer = payload_equalizer = digital.ofdm_equalizer_simpledfe(fft_len, payload_mod_2.base(), occupied_carriers, pilot_carriers, pilot_symbols, 1)
        self.packet_len = packet_len = 96
        self.header_formatter = header_formatter = digital.packet_header_ofdm(occupied_carriers, n_syms=1, len_tag_key=packet_length_tag_key, frame_len_tag_key=length_tag_key, bits_per_header_sym=header_mod.bits_per_symbol(), bits_per_payload_sym=payload_mod.bits_per_symbol(), scramble_header=False)
        self.header_equalizer = header_equalizer = ofdm_allocator.ofdm_equalizer_simpledfe_alix(fft_len, header_mod.base(), occupied_carriers, pilot_carriers, pilot_symbols)

        ##################################################
        # Blocks
        ##################################################
        self.ofdm_allocator_vector_source_tagged_0_0 = ofdm_allocator.vector_source_tagged(variable_0, True, 1, True, packet_length_tag_key, [])
        self.ofdm_allocator_vector_source_tagged_0 = ofdm_allocator.vector_source_tagged(variable_0, True, 1, True, length_tag_key, [])
        self.ofdm_allocator_serializer_subcarrier_0_0 = ofdm_allocator.serializer_subcarrier(fft_len, 1, length_tag_key, packet_length_tag_key, 0, "", False)
        self.ofdm_allocator_serializer_subcarrier_0 = ofdm_allocator.serializer_subcarrier(fft_len, 1, length_tag_key, "", 0, "", True)
        self.ofdm_allocator_ofdm_tx_0 = ofdm_allocator.ofdm_tx(fft_len=64, cp_len=16,
            packet_length_tag_key="packet_len",
            pilot_carriers=pilot_carriers,
            pilot_symbols=pilot_symbols,
            sync_word1=sync_word1,
            sync_word2=sync_word2,
            bps_header=1,
            bps_payload=2,
            rolloff=0,
            debug_log=False,
            scramble_bits=False
            )
        self.ofdm_allocator_frame_equalizer_alix_0 = ofdm_allocator.frame_equalizer_alix(header_equalizer.base(), 1, fft_len/4, length_tag_key, True, 1)
        self.ofdm_allocator_constellation_decoder_alix_0 = ofdm_allocator.constellation_decoder_alix(header_mod.base())
        self.fft_vxx_1 = fft.fft_vcc(fft_len, True, (), True, 1)
        self.fft_vxx_0 = fft.fft_vcc(fft_len, True, (()), True, 1)
        self.digital_packet_headerparser_b_0 = digital.packet_headerparser_b(header_formatter.base())
        self.digital_ofdm_sync_sc_cfb_0 = digital.ofdm_sync_sc_cfb(fft_len, fft_len/4, False)
        self.digital_ofdm_frame_equalizer_vcvc_1 = digital.ofdm_frame_equalizer_vcvc(payload_equalizer.base(), fft_len/4, length_tag_key, False, 0)
        self.digital_ofdm_chanest_vcvc_0 = digital.ofdm_chanest_vcvc((sync_word1), (sync_word2), 1, 0, 3, False)
        self.digital_header_payload_demux_0 = digital.header_payload_demux(
        	  3,
        	  fft_len,
        	  fft_len/4,
        	  length_tag_key,
        	  "",
        	  True,
        	  gr.sizeof_gr_complex,
        	  "rx_time",
                  samp_rate,
                  (),
            )
        self.digital_crc32_bb_0 = digital.crc32_bb(True, packet_length_tag_key, True)
        self.digital_constellation_decoder_cb_1 = digital.constellation_decoder_cb(payload_mod_2.base())
        self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=0.1,
        	frequency_offset=0 * 1.0/fft_len,
        	epsilon=1.0,
        	taps=(1.0, ),
        	noise_seed=0,
        	block_tags=True
        )
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_tagged_stream_to_pdu_0 = blocks.tagged_stream_to_pdu(blocks.byte_t, packet_length_tag_key)
        self.blocks_tag_debug_1 = blocks.tag_debug(gr.sizeof_char*1, "Rx Bytes", ""); self.blocks_tag_debug_1.set_display(False)
        self.blocks_repack_bits_bb_0 = blocks.repack_bits_bb(payload_mod.bits_per_symbol(), 8, packet_length_tag_key, True, gr.GR_LSB_FIRST)
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.byte_t, packet_length_tag_key)
        self.blocks_multiply_xx_0 = blocks.multiply_vcc(1)
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.cons(pmt.make_dict(), pmt.pmt_to_python.numpy_to_uvector(numpy.array([ord(c) for c in "Hello world! It is a proof, I hope it works!"], numpy.uint8))), 100)
        self.blocks_message_debug_0 = blocks.message_debug()
        self.blocks_delay_0 = blocks.delay(gr.sizeof_gr_complex*1, fft_len+fft_len/4)
        self.analog_frequency_modulator_fc_0 = analog.frequency_modulator_fc(-2.0/fft_len)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.blocks_pdu_to_tagged_stream_0, 'pdus'))    
        self.msg_connect((self.blocks_tagged_stream_to_pdu_0, 'pdus'), (self.blocks_message_debug_0, 'print'))    
        self.msg_connect((self.digital_packet_headerparser_b_0, 'header_data'), (self.digital_header_payload_demux_0, 'header_data'))    
        self.connect((self.analog_frequency_modulator_fc_0, 0), (self.blocks_multiply_xx_0, 0))    
        self.connect((self.blocks_delay_0, 0), (self.blocks_multiply_xx_0, 1))    
        self.connect((self.blocks_multiply_xx_0, 0), (self.digital_header_payload_demux_0, 0))    
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.ofdm_allocator_ofdm_tx_0, 0))    
        self.connect((self.blocks_repack_bits_bb_0, 0), (self.digital_crc32_bb_0, 0))    
        self.connect((self.blocks_throttle_0, 0), (self.blocks_delay_0, 0))    
        self.connect((self.blocks_throttle_0, 0), (self.digital_ofdm_sync_sc_cfb_0, 0))    
        self.connect((self.channels_channel_model_0, 0), (self.blocks_throttle_0, 0))    
        self.connect((self.digital_constellation_decoder_cb_1, 0), (self.blocks_repack_bits_bb_0, 0))    
        self.connect((self.digital_crc32_bb_0, 0), (self.blocks_tag_debug_1, 0))    
        self.connect((self.digital_crc32_bb_0, 0), (self.blocks_tagged_stream_to_pdu_0, 0))    
        self.connect((self.digital_header_payload_demux_0, 0), (self.fft_vxx_0, 0))    
        self.connect((self.digital_header_payload_demux_0, 1), (self.fft_vxx_1, 0))    
        self.connect((self.digital_ofdm_chanest_vcvc_0, 0), (self.ofdm_allocator_frame_equalizer_alix_0, 0))    
        self.connect((self.digital_ofdm_frame_equalizer_vcvc_1, 0), (self.ofdm_allocator_serializer_subcarrier_0_0, 0))    
        self.connect((self.digital_ofdm_sync_sc_cfb_0, 0), (self.analog_frequency_modulator_fc_0, 0))    
        self.connect((self.digital_ofdm_sync_sc_cfb_0, 1), (self.digital_header_payload_demux_0, 1))    
        self.connect((self.fft_vxx_0, 0), (self.digital_ofdm_chanest_vcvc_0, 0))    
        self.connect((self.fft_vxx_1, 0), (self.digital_ofdm_frame_equalizer_vcvc_1, 0))    
        self.connect((self.ofdm_allocator_constellation_decoder_alix_0, 0), (self.digital_packet_headerparser_b_0, 0))    
        self.connect((self.ofdm_allocator_frame_equalizer_alix_0, 0), (self.ofdm_allocator_serializer_subcarrier_0, 0))    
        self.connect((self.ofdm_allocator_ofdm_tx_0, 0), (self.channels_channel_model_0, 0))    
        self.connect((self.ofdm_allocator_serializer_subcarrier_0, 0), (self.ofdm_allocator_constellation_decoder_alix_0, 0))    
        self.connect((self.ofdm_allocator_serializer_subcarrier_0_0, 0), (self.digital_constellation_decoder_cb_1, 0))    
        self.connect((self.ofdm_allocator_vector_source_tagged_0, 0), (self.ofdm_allocator_frame_equalizer_alix_0, 1))    
        self.connect((self.ofdm_allocator_vector_source_tagged_0, 0), (self.ofdm_allocator_serializer_subcarrier_0, 1))    
        self.connect((self.ofdm_allocator_vector_source_tagged_0, 0), (self.ofdm_allocator_serializer_subcarrier_0_0, 1))    
        self.connect((self.ofdm_allocator_vector_source_tagged_0_0, 0), (self.ofdm_allocator_ofdm_tx_0, 1))    

    def get_pilot_symbols(self):
        return self.pilot_symbols

    def set_pilot_symbols(self, pilot_symbols):
        self.pilot_symbols = pilot_symbols
        self.set_header_equalizer(ofdm_allocator.ofdm_equalizer_simpledfe_alix(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod_2.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))

    def get_pilot_carriers(self):
        return self.pilot_carriers

    def set_pilot_carriers(self, pilot_carriers):
        self.pilot_carriers = pilot_carriers
        self.set_header_equalizer(ofdm_allocator.ofdm_equalizer_simpledfe_alix(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod_2.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))

    def get_payload_mod_2(self):
        return self.payload_mod_2

    def set_payload_mod_2(self, payload_mod_2):
        self.payload_mod_2 = payload_mod_2
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod_2.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))

    def get_payload_mod(self):
        return self.payload_mod

    def set_payload_mod(self, payload_mod):
        self.payload_mod = payload_mod
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))
        self.blocks_repack_bits_bb_0.set_k_and_l(self.payload_mod.bits_per_symbol(),8)

    def get_packet_length_tag_key(self):
        return self.packet_length_tag_key

    def set_packet_length_tag_key(self, packet_length_tag_key):
        self.packet_length_tag_key = packet_length_tag_key
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))

    def get_occupied_carriers(self):
        return self.occupied_carriers

    def set_occupied_carriers(self, occupied_carriers):
        self.occupied_carriers = occupied_carriers
        self.set_header_equalizer(ofdm_allocator.ofdm_equalizer_simpledfe_alix(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod_2.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))

    def get_length_tag_key(self):
        return self.length_tag_key

    def set_length_tag_key(self, length_tag_key):
        self.length_tag_key = length_tag_key
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))

    def get_header_mod(self):
        return self.header_mod

    def set_header_mod(self, header_mod):
        self.header_mod = header_mod
        self.set_header_equalizer(ofdm_allocator.ofdm_equalizer_simpledfe_alix(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_header_formatter(digital.packet_header_ofdm(self.occupied_carriers, n_syms=1, len_tag_key=self.packet_length_tag_key, frame_len_tag_key=self.length_tag_key, bits_per_header_sym=self.header_mod.bits_per_symbol(), bits_per_payload_sym=self.payload_mod.bits_per_symbol(), scramble_header=False))

    def get_fft_len(self):
        return self.fft_len

    def set_fft_len(self, fft_len):
        self.fft_len = fft_len
        self.set_header_equalizer(ofdm_allocator.ofdm_equalizer_simpledfe_alix(self.fft_len, self.header_mod.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols))
        self.set_payload_equalizer(digital.ofdm_equalizer_simpledfe(self.fft_len, self.payload_mod_2.base(), self.occupied_carriers, self.pilot_carriers, self.pilot_symbols, 1))
        self.analog_frequency_modulator_fc_0.set_sensitivity(-2.0/self.fft_len)
        self.blocks_delay_0.set_dly(self.fft_len+self.fft_len/4)
        self.channels_channel_model_0.set_frequency_offset(0 * 1.0/self.fft_len)

    def get_variable_0(self):
        return self.variable_0

    def set_variable_0(self, variable_0):
        self.variable_0 = variable_0
        self.ofdm_allocator_vector_source_tagged_0_0.set_data(self.variable_0, [])
        self.ofdm_allocator_vector_source_tagged_0.set_data(self.variable_0, [])

    def get_sync_word2(self):
        return self.sync_word2

    def set_sync_word2(self, sync_word2):
        self.sync_word2 = sync_word2

    def get_sync_word1(self):
        return self.sync_word1

    def set_sync_word1(self, sync_word1):
        self.sync_word1 = sync_word1

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_payload_equalizer(self):
        return self.payload_equalizer

    def set_payload_equalizer(self, payload_equalizer):
        self.payload_equalizer = payload_equalizer

    def get_packet_len(self):
        return self.packet_len

    def set_packet_len(self, packet_len):
        self.packet_len = packet_len

    def get_header_formatter(self):
        return self.header_formatter

    def set_header_formatter(self, header_formatter):
        self.header_formatter = header_formatter

    def get_header_equalizer(self):
        return self.header_equalizer

    def set_header_equalizer(self, header_equalizer):
        self.header_equalizer = header_equalizer


def main(top_block_cls=rx_ofdm, options=None):

    tb = top_block_cls()
    tb.start()
    try:
        raw_input('Press Enter to quit: ')
    except EOFError:
        pass
    tb.stop()
    tb.wait()


if __name__ == '__main__':
    main()
