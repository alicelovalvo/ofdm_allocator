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

#ifndef INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_PARSER_ALIX_IMPL_H
#define INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_PARSER_ALIX_IMPL_H

#include <ofdm_allocator/packet_header_parser_alix.h>
#include <boost/crc.hpp>

namespace gr {
  namespace ofdm_allocator {

    class packet_header_parser_alix_impl : public packet_header_parser_alix
    {
     private:
       packet_header_default_alix::sptr d_header_formatter;
       int d_bits_per_byte;
       unsigned d_mask;
       pmt::pmt_t d_len_tag_key; //!< Key of the length tag
       pmt::pmt_t d_num_tag_key;
       boost::crc_optimal<8, 0x07, 0xFF, 0x00, false, false>  d_crc_impl;

     public:
      packet_header_parser_alix_impl(const gr::ofdm_allocator::packet_header_default_alix::sptr &header_formatter, const std::string &len_tag_key, const std::string &num_tag_key);
      ~packet_header_parser_alix_impl();

      bool header_parser_alix(const unsigned char *in, int header_length, std::vector<tag_t> &tags);

      // int get_header_len_from_occupied_carriers(const std::vector<std::vector<int> > &occupied_carriers, int n_syms);
      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_PARSER_ALIX_IMPL_H */
