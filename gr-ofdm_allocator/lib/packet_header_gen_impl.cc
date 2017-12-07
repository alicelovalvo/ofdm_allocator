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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <boost/format.hpp>
#include <gnuradio/io_signature.h>
#include "packet_header_gen_impl.h"

namespace gr {
  namespace ofdm_allocator {

    packet_header_gen::sptr
    packet_header_gen::make(
    const packet_header_default_alix::sptr &header_formatter,
    int vector_len,
    const std::string &len_tag_key
    )
    {
      return gnuradio::get_initial_sptr (new packet_header_gen_impl(header_formatter, vector_len, len_tag_key));
    }


    packet_header_gen::sptr
    packet_header_gen::make(
      long header_len,
      int vector_len,
      const std::string &len_tag_key
    )
    {
      const packet_header_default_alix::sptr header_formatter(
    new packet_header_default_alix(header_len, len_tag_key)
      );
      return gnuradio::get_initial_sptr (new packet_header_gen_impl(header_formatter, vector_len, len_tag_key));
    }

    const unsigned MASK_LUT[9] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x2F, 0x7F, 0xFF};
    packet_header_gen_impl::packet_header_gen_impl(
        const gr::ofdm_allocator::packet_header_default_alix::sptr &header_formatter,
        int vector_len,
        const std::string &len_tag_key
        )
      : tagged_stream_block("packet_header_gen",
           io_signature::make2(2, 2, sizeof (char), sizeof(int)*vector_len),
           io_signature::make(1, 1, sizeof (char)),
           len_tag_key),
      d_formatter(header_formatter),
      d_bits_per_byte(1),//bits_per_header_sym),
      d_header_number(0)
    {
      if (d_bits_per_byte < 1 || d_bits_per_byte > 8) {
	throw std::invalid_argument("bits_per_byte must be in [1, 8]");
      }
      d_mask = MASK_LUT[d_bits_per_byte];

      set_output_multiple(d_formatter->header_len());
      // This is the worst case rate, because we don't know the true value, of course
      set_relative_rate(d_formatter->header_len());
      set_tag_propagation_policy(TPP_DONT);
    }

    int packet_header_gen_impl::get_header_len_from_occupied_carriers(const std::vector<std::vector<int> > &occupied_carriers, int n_syms)
    {
      int header_len = 0;
      for (int i = 0; i < n_syms; i++) {
	header_len += occupied_carriers[i].size();
      }

      return header_len;
    }

    bool packet_header_gen_impl::header_formatter_alix(
  long packet_len,
  int header_len,
        unsigned char *out,

  const std::vector<tag_t> &tags
    )
    {
      packet_len &= 0x0FFF;
      d_crc_impl.reset();
      d_crc_impl.process_bytes((void const *) &packet_len, 2);
      d_crc_impl.process_bytes((void const *) &d_header_number, 2);
      unsigned char crc = d_crc_impl();

      memset(out, 0x00, header_len);
      int k = 0; // Position in out
      for (int i = 0; i < 12 && k < header_len; i += d_bits_per_byte, k++) {
  out[k] = (unsigned char) ((packet_len >> i) & d_mask);
      }
      for (int i = 0; i < 12 && k < header_len; i += d_bits_per_byte, k++) {
  out[k] = (unsigned char) ((d_header_number >> i) & d_mask);
      }
      for (int i = 0; i < 8 && k < header_len; i += d_bits_per_byte, k++) {
  out[k] = (unsigned char) ((crc >> i) & d_mask);
      }
      d_header_number++;
      d_header_number &= 0x0FFF;

      return true;
    }

    void
    packet_header_gen_impl::set_header_formatter(packet_header_default_alix::sptr header_formatter)
    {
      gr::thread::scoped_lock guard(d_setlock);
      d_formatter=header_formatter;
    }
    packet_header_gen_impl::~packet_header_gen_impl()
    {
    }

    int
    packet_header_gen_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      gr::thread::scoped_lock guard(d_setlock);
      unsigned char *out = (unsigned char *) output_items[0];
      int *in2 = (int *) input_items[1];

      // std::cout << "/* message ninput_items */" << ninput_items[1] << '\n';
      // std::cout << "/* in2 */";
      // for(int j=0; j < ninput_items[1]; j++){
      //   std::cout << in2[j] << ", ";
      // }
      // std::cout << '\n';

      std::vector<int> vector_sub;
      std::vector<std::vector<int> > vector_vector_sub;

      for (int i=0; i< (ninput_items[1]/48); i++){
        // std::cout << "in2 : " ;
       for(int j=0; j < 48; j++){
         int cycle = i*48;
         if (in2[j+cycle] == 0){
           continue;
        }
        else{
          vector_sub.push_back(in2[j+cycle]);
        }
      }
      if (vector_sub.size()!=0){
        vector_vector_sub.push_back(vector_sub);
        // std::cout << "##############################" << '\n';
        vector_sub.erase(vector_sub.begin(),vector_sub.end());
      }
    }

      // for (int l=0; l<vector_vector_sub.size();l++){
      //   std::cout << "/* in2_vector: */";
      //   for (int i=0; i<vector_vector_sub[l].size(); i++){
      //     std::cout << vector_vector_sub[l][i] << ", ";
      //   }
      //   std::cout << '\n';
      // }

      int header_len = packet_header_gen_impl::get_header_len_from_occupied_carriers(vector_vector_sub, d_bits_per_byte);

      // std::cout << "/* header_len */" << header_len << '\n';

      std::vector<tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + ninput_items[0]);
      // bool ciao = packet_header_gen_impl::header_formatter_alix(ninput_items[0], header_len, out, tags);

      // std::cout << "/* message ciao */" << ciao << '\n';

      // get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + ninput_items[0]);
    //   if (!d_formatter->header_formatter(ninput_items[0], out, tags)) {
    // GR_LOG_FATAL(d_logger, boost::format("header_formatter() returned false (this shouldn't happen). Offending header started at %1%") % nitems_read(0));
    // throw std::runtime_error("header formatter returned false.");
    //   }
      if (!packet_header_gen_impl::header_formatter_alix(ninput_items[0], header_len, out, tags)) {
    GR_LOG_FATAL(d_logger, boost::format("header_formatter() returned false (this shouldn't happen). Offending header started at %1%") % nitems_read(0));
    throw std::runtime_error("header formatter returned false.");
      }

      return header_len;
      // return d_formatter->header_len();
    }

  } /* namespace ofdm_allocator */
} /* namespace gr */
