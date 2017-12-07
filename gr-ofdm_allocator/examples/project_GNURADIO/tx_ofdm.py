#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: OFDM Tx
# Description: Example of an OFDM Transmitter
# Generated: Tue Dec  5 17:27:10 2017
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from gnuradio import blocks
from gnuradio import channels
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import fft
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.digital.utils import tagged_streams
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from gnuradio.wxgui import fftsink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import numpy
import ofdm_allocator
import pmt
import random
import wx


class tx_ofdm(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="OFDM Tx")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.variable_0 = variable_0 = (range(-26,-21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22,27))
        self.length_tag_key = length_tag_key = "packet_len"
        self.variable_1 = variable_1 = (range(-26, -21) + range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21),)
        self.sync_word2 = sync_word2 = [0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 1, 1, -1, -1, -1, 1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, 1, -1, -1, 1, -1, 0, 1, -1, 1, 1, 1, -1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, -1, -1, -1, 1, -1, 1, -1, -1, -1, -1, 0, 0, 0, 0, 0] 
        self.sync_word1 = sync_word1 = [0., 0., 0., 0., 0., 0., 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., -1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., -1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 1.41421356, 0., 0., 0., 0., 0., 0.]
        self.samp_rate = samp_rate = 10000
        self.rolloff = rolloff = 0
        self.pilot_symbols = pilot_symbols = ((1, 1, 1, -1,),)
        self.pilot_carriers = pilot_carriers = ((-21, -7, 7, 21,),)
        self.payload_mod = payload_mod = digital.constellation_qpsk()
        self.packet_len = packet_len = 96
        self.occupied_carriers = occupied_carriers = (range(-20, -7) + range(-6, 0) + range(1, 7) + range(8, 21) + range(22,27),)
        self.header_mod = header_mod = digital.constellation_bpsk()
        self.header_formatter = header_formatter = ofdm_allocator.packet_header_ofdm_alix((variable_0,), 1, length_tag_key, "frame_len", "packet_num",1,1,False)
        self.fft_len = fft_len = 64

        ##################################################
        # Blocks
        ##################################################
        self.wxgui_fftsink2_0_0 = fftsink2.fft_sink_c(
        	self.GetWin(),
        	baseband_freq=0,
        	y_per_div=10,
        	y_divs=10,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=80,
        	fft_rate=22,
        	average=False,
        	avg_alpha=None,
        	title="FFT Plot",
        	peak_hold=False,
        )
        self.Add(self.wxgui_fftsink2_0_0.win)
        self.ofdm_allocator_vector_source_tagged_0 = ofdm_allocator.vector_source_tagged(variable_0, True, 1, True, length_tag_key, [])
        self.ofdm_allocator_packet_header_gen_0 = ofdm_allocator.packet_header_gen(header_formatter.formatter(), 1, length_tag_key)
        self.ofdm_allocator_allocator_subcarrier_0 = ofdm_allocator.allocator_subcarrier(fft_len, 1, pilot_carriers, pilot_symbols, (sync_word1,sync_word2), length_tag_key, True)
        self.fft_vxx_0_0 = fft.fft_vcc(fft_len, False, (()), True, 1)
        self.digital_ofdm_rx_0 = digital.ofdm_rx(
        	  fft_len=fft_len, cp_len=fft_len/4,
        	  frame_length_tag_key='frame_'+"length",
        	  packet_length_tag_key="length",
        	  occupied_carriers=(variable_0,),
        	  pilot_carriers=pilot_carriers,
        	  pilot_symbols=pilot_symbols,
        	  sync_word1=sync_word1,
        	  sync_word2=sync_word2,
        	  bps_header=1,
        	  bps_payload=2,
        	  debug_log=False,
        	  scramble_bits=False
        	 )
        self.digital_ofdm_cyclic_prefixer_0_0 = digital.ofdm_cyclic_prefixer(fft_len, fft_len+fft_len/4, rolloff, length_tag_key)
        self.digital_crc32_bb_0 = digital.crc32_bb(False, length_tag_key, True)
        self.digital_chunks_to_symbols_xx_0_0 = digital.chunks_to_symbols_bc((payload_mod.points()), 1)
        self.digital_chunks_to_symbols_xx_0 = digital.chunks_to_symbols_bc((header_mod.points()), 1)
        self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=0.0,
        	frequency_offset=0.0,
        	epsilon=1.0,
        	taps=(1.0 + 1.0j, ),
        	noise_seed=0,
        	block_tags=True
        )
        self.blocks_throttle_0_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_tagged_stream_to_pdu_0 = blocks.tagged_stream_to_pdu(blocks.byte_t, "length")
        self.blocks_tagged_stream_mux_0 = blocks.tagged_stream_mux(gr.sizeof_gr_complex*1, length_tag_key, 0)
        self.blocks_tag_gate_0_0 = blocks.tag_gate(gr.sizeof_gr_complex * 1, False)
        self.blocks_repack_bits_bb_0 = blocks.repack_bits_bb(8, payload_mod.bits_per_symbol(), length_tag_key, False, gr.GR_LSB_FIRST)
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.byte_t, "packet_len")
        self.blocks_multiply_const_vxx_0_0 = blocks.multiply_const_vcc((0.05, ))
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.cons(pmt.make_dict(), pmt.pmt_to_python.numpy_to_uvector(numpy.array([ord(c) for c in "Hello world! It is a proof, I hope it works!"], numpy.uint8))), 100)
        self.blocks_message_debug_0 = blocks.message_debug()

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_message_strobe_0, 'strobe'), (self.blocks_pdu_to_tagged_stream_0, 'pdus'))    
        self.msg_connect((self.blocks_tagged_stream_to_pdu_0, 'pdus'), (self.blocks_message_debug_0, 'print'))    
        self.connect((self.blocks_multiply_const_vxx_0_0, 0), (self.blocks_tag_gate_0_0, 0))    
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.digital_crc32_bb_0, 0))    
        self.connect((self.blocks_repack_bits_bb_0, 0), (self.digital_chunks_to_symbols_xx_0_0, 0))    
        self.connect((self.blocks_tag_gate_0_0, 0), (self.blocks_throttle_0_0, 0))    
        self.connect((self.blocks_tagged_stream_mux_0, 0), (self.ofdm_allocator_allocator_subcarrier_0, 0))    
        self.connect((self.blocks_throttle_0_0, 0), (self.channels_channel_model_0, 0))    
        self.connect((self.blocks_throttle_0_0, 0), (self.wxgui_fftsink2_0_0, 0))    
        self.connect((self.channels_channel_model_0, 0), (self.digital_ofdm_rx_0, 0))    
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.blocks_tagged_stream_mux_0, 0))    
        self.connect((self.digital_chunks_to_symbols_xx_0_0, 0), (self.blocks_tagged_stream_mux_0, 1))    
        self.connect((self.digital_crc32_bb_0, 0), (self.blocks_repack_bits_bb_0, 0))    
        self.connect((self.digital_crc32_bb_0, 0), (self.ofdm_allocator_packet_header_gen_0, 0))    
        self.connect((self.digital_ofdm_cyclic_prefixer_0_0, 0), (self.blocks_multiply_const_vxx_0_0, 0))    
        self.connect((self.digital_ofdm_rx_0, 0), (self.blocks_tagged_stream_to_pdu_0, 0))    
        self.connect((self.fft_vxx_0_0, 0), (self.digital_ofdm_cyclic_prefixer_0_0, 0))    
        self.connect((self.ofdm_allocator_allocator_subcarrier_0, 0), (self.fft_vxx_0_0, 0))    
        self.connect((self.ofdm_allocator_packet_header_gen_0, 0), (self.digital_chunks_to_symbols_xx_0, 0))    
        self.connect((self.ofdm_allocator_vector_source_tagged_0, 0), (self.ofdm_allocator_allocator_subcarrier_0, 1))    
        self.connect((self.ofdm_allocator_vector_source_tagged_0, 0), (self.ofdm_allocator_packet_header_gen_0, 1))    

    def get_variable_0(self):
        return self.variable_0

    def set_variable_0(self, variable_0):
        self.variable_0 = variable_0
        self.set_header_formatter(ofdm_allocator.packet_header_ofdm_alix((self.variable_0,), 1, self.length_tag_key, "frame_len", "packet_num",1,1,False))
        self.ofdm_allocator_vector_source_tagged_0.set_data(self.variable_0, [])

    def get_length_tag_key(self):
        return self.length_tag_key

    def set_length_tag_key(self, length_tag_key):
        self.length_tag_key = length_tag_key
        self.set_header_formatter(ofdm_allocator.packet_header_ofdm_alix((self.variable_0,), 1, self.length_tag_key, "frame_len", "packet_num",1,1,False))

    def get_variable_1(self):
        return self.variable_1

    def set_variable_1(self, variable_1):
        self.variable_1 = variable_1

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
        self.blocks_throttle_0_0.set_sample_rate(self.samp_rate)
        self.wxgui_fftsink2_0_0.set_sample_rate(self.samp_rate)

    def get_rolloff(self):
        return self.rolloff

    def set_rolloff(self, rolloff):
        self.rolloff = rolloff

    def get_pilot_symbols(self):
        return self.pilot_symbols

    def set_pilot_symbols(self, pilot_symbols):
        self.pilot_symbols = pilot_symbols

    def get_pilot_carriers(self):
        return self.pilot_carriers

    def set_pilot_carriers(self, pilot_carriers):
        self.pilot_carriers = pilot_carriers

    def get_payload_mod(self):
        return self.payload_mod

    def set_payload_mod(self, payload_mod):
        self.payload_mod = payload_mod
        self.blocks_repack_bits_bb_0.set_k_and_l(8,self.payload_mod.bits_per_symbol())
        self.digital_chunks_to_symbols_xx_0_0.set_symbol_table((self.payload_mod.points()))

    def get_packet_len(self):
        return self.packet_len

    def set_packet_len(self, packet_len):
        self.packet_len = packet_len

    def get_occupied_carriers(self):
        return self.occupied_carriers

    def set_occupied_carriers(self, occupied_carriers):
        self.occupied_carriers = occupied_carriers

    def get_header_mod(self):
        return self.header_mod

    def set_header_mod(self, header_mod):
        self.header_mod = header_mod
        self.digital_chunks_to_symbols_xx_0.set_symbol_table((self.header_mod.points()))

    def get_header_formatter(self):
        return self.header_formatter

    def set_header_formatter(self, header_formatter):
        self.header_formatter = header_formatter
        self.ofdm_allocator_packet_header_gen_0.set_header_formatter(self.header_formatter.formatter())

    def get_fft_len(self):
        return self.fft_len

    def set_fft_len(self, fft_len):
        self.fft_len = fft_len


def main(top_block_cls=tx_ofdm, options=None):

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()
