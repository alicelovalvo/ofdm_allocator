# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
install(FILES
    ofdm_allocator_vector_source_tagged.xml
    ofdm_allocator_allocator_subcarrier.xml
    ofdm_allocator_ofdm_tx.xml
    ofdm_allocator_serializer_subcarrier.xml
    ofdm_allocator_packet_header_default_alix.xml
    ofdm_allocator_packet_header_gen.xml
    ofdm_allocator_packet_header_ofdm_alix.xml
    ofdm_allocator_ofdm_equalizer_base_alix.xml
    ofdm_allocator_ofdm_equalizer_simpledfe_alix.xml
    ofdm_allocator_frame_equalizer_alix.xml
    ofdm_allocator_constellation_alix.xml
    ofdm_allocator_metric_type_alix.xml
    ofdm_allocator_constellation_decoder_alix.xml DESTINATION share/gnuradio/grc/blocks
)
