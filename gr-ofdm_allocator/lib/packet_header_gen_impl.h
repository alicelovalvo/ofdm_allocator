/* -*- c++ -*- */
/*
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_GEN_IMPL_H
#define INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_GEN_IMPL_H

#include <ofdm_allocator/packet_header_gen.h>
#include <boost/crc.hpp>

namespace gr {
  namespace ofdm_allocator {

    class packet_header_gen_impl : public packet_header_gen
    {
     private:
       gr::ofdm_allocator::packet_header_default_alix::sptr d_formatter;
       int d_bits_per_byte;
       unsigned d_header_number;
       unsigned d_mask;
       boost::crc_optimal<8, 0x07, 0xFF, 0x00, false, false>  d_crc_impl;

      // Nothing to declare in this block.

    public:
     packet_header_gen_impl(
    const packet_header_default_alix::sptr &header_formatter,
    int vector_len,
    const std::string &len_tag_key
     );
     ~packet_header_gen_impl();

     int get_header_len_from_occupied_carriers(const std::vector<std::vector<int> > &occupied_carriers, int n_syms);
     bool header_formatter_alix(long packet_len, int header_len, unsigned char *out, const std::vector<tag_t> &tags);
     void set_header_formatter(packet_header_default_alix::sptr header_formatter);

     void remove_length_tags(const std::vector<std::vector<tag_t> > &tags) {};
     int calculate_output_stream_length(const gr_vector_int &ninput_items) { return d_formatter->header_len(); };

     int work(int noutput_items,
    gr_vector_int &ninput_items,
    gr_vector_const_void_star &input_items,
    gr_vector_void_star &output_items);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_GEN_IMPL_H */
