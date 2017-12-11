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
#include "packet_header_parser_alix_impl.h"

#define msg_port_id     pmt::mp("header_data")

namespace gr {
  namespace ofdm_allocator {

    packet_header_parser_alix::sptr
    packet_header_parser_alix::make(long header_len,
      const std::string &len_tag_key,
      const std::string &num_tag_key)
    {
      const packet_header_default_alix::sptr header_formatter(
    new packet_header_default_alix(header_len, len_tag_key)
      );
      return gnuradio::get_initial_sptr (new packet_header_parser_alix_impl(header_formatter, len_tag_key, num_tag_key));
    }

    packet_header_parser_alix::sptr
    packet_header_parser_alix::make(const gr::ofdm_allocator::packet_header_default_alix::sptr &header_formatter, const std::string &len_tag_key, const std::string &num_tag_key)
    {
      return gnuradio::get_initial_sptr (new packet_header_parser_alix_impl(header_formatter, len_tag_key, num_tag_key));
    }

    const unsigned MASK_LUT[9] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x2F, 0x7F, 0xFF};
    packet_header_parser_alix_impl::packet_header_parser_alix_impl(const gr::ofdm_allocator::packet_header_default_alix::sptr &header_formatter, const std::string &len_tag_key, const std::string &num_tag_key)
      : sync_block("packet_header_parser_alix",
          io_signature::make2(2, 2, sizeof (unsigned char), sizeof(int)),
          io_signature::make(0, 0, 0)),
      d_header_formatter(header_formatter),
        d_bits_per_byte(1),
        d_len_tag_key(d_header_formatter->len_tag_key()),
        //d_num_tag_key(num_tag_key.empty() ? pmt::PMT_NIL : pmt::string_to_symbol(num_tag_key))
         d_num_tag_key(pmt::PMT_NIL)
    {
      if (d_bits_per_byte < 1 || d_bits_per_byte > 8) {
	throw std::invalid_argument("bits_per_byte must be in [1, 8]");
      }
      d_mask = MASK_LUT[d_bits_per_byte];

      message_port_register_out(msg_port_id);
      set_output_multiple(header_formatter->header_len());
    }

    packet_header_parser_alix_impl::~packet_header_parser_alix_impl()
    {
    }

    //   int packet_header_parser_alix_impl::get_header_len_from_occupied_carriers(const std::vector<std::vector<int> > &occupied_carriers, int n_syms)
    //   {
    //     int header_len = 0;
    //     for (int i = 0; i < n_syms; i++) {
    // header_len += occupied_carriers[i].size();
    //     }
    //
    //     return header_len;
    //   }

    bool packet_header_parser_alix_impl::header_parser_alix(
      const unsigned char *in,
      int header_length,
      std::vector<tag_t> &tags)
      {
        unsigned header_len = 0;
        unsigned header_num = 0;
        tag_t tag;

        int k = 0; // Position in "in"
        for (int i = 0; i < 12 && k < header_length; i += d_bits_per_byte, k++) {
          header_len |= (((int) in[k]) & d_mask) << i;
        }
        tag.key = d_len_tag_key;
        tag.value = pmt::from_long(header_len);
        tags.push_back(tag);
        if (k >= header_length) {
          return true;
        }
        std::cout << "/* message */" << d_num_tag_key << '\n';
        if (d_num_tag_key == pmt::PMT_NIL) {
          k += 12;
        } else {
          for (int i = 0; i < 12 && k < header_length; i += d_bits_per_byte, k++) {
            header_num |= (((int) in[k]) & d_mask) << i;
          }
          tag.key = d_num_tag_key;
          tag.value = pmt::from_long(header_num);
          tags.push_back(tag);
        }
        if (k >= header_length) {
          return true;
        }

        d_crc_impl.reset();
        d_crc_impl.process_bytes((void const *) &header_len, 2);
        d_crc_impl.process_bytes((void const *) &header_num, 2);
        unsigned char crc_calcd = d_crc_impl();
        for (int i = 0; i < 8 && k < header_length; i += d_bits_per_byte, k++) {
          if ( (((int) in[k]) & d_mask) != (((int) crc_calcd >> i) & d_mask) ) {
            return false;
          }
        }

        return true;
      }

      int
      packet_header_parser_alix_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
        {
          const unsigned char *in = (const unsigned char *) input_items[0];

          // std::cout << "/* message */" << '\n';
          int in2;
          for (size_t i = 0; i < noutput_items; i++){
            in2 = ((int *) input_items[1])[i];
          }
          std::cout << "/* in2.size */" << in2 << '\n';
          // std::cout << "/* message ninput_items */" << ninput_items[1] << '\n';
          // std::cout << "/* in2 */";
          // for(int j=0; j < ninput_items[1]; j++){
          //   std::cout << in2[j] << ", ";
          // }
          // std::cout << '\n';
// std::cout << "/* message */" << d_num_tag_key << '\n';
          // int header_len = packet_header_parser_alix_impl::get_header_len_from_occupied_carriers(vector_vector_sub, d_bits_per_byte);

          if (noutput_items < in2){//d_header_formatter->header_len()) {
            return 0;
          }

      std::vector<tag_t> tags;
      get_tags_in_range(
    tags, 0,
    nitems_read(0),
    nitems_read(0)+in2//d_header_formatter->header_len()
      );

      if (!d_header_formatter->header_parser(in, in2, tags)) {
      // if (!packet_header_parser_alix_impl::header_parser_alix(in, in2, tags)) {
  GR_LOG_INFO(d_logger, boost::format("Detected an invalid packet at item %1%") % nitems_read(0));
  message_port_pub(msg_port_id, pmt::PMT_F);
      } else {
  pmt::pmt_t dict(pmt::make_dict());
  for (unsigned i = 0; i < tags.size(); i++) {
    dict = pmt::dict_add(dict, tags[i].key, tags[i].value);
  }
  message_port_pub(msg_port_id, dict);
      }

      return in2;//d_header_formatter->header_len();
    }

  } /* namespace ofdm_allocator */
} /* namespace gr */
