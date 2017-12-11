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

#include <gnuradio/io_signature.h>
#include <iostream>
#include <ofdm_allocator/packet_header_ofdm_alix.h>
#include <gnuradio/digital/lfsr.h>

namespace gr {
  namespace ofdm_allocator {

    int _get_header_len_from_occupied_carriers(const std::vector<std::vector<int> > &occupied_carriers, int n_syms)
    {
      int header_len = 0;
      for (int i = 0; i < n_syms; i++) {
	header_len += occupied_carriers[i].size();
      }

      return header_len;
    }

    packet_header_ofdm_alix::sptr
    packet_header_ofdm_alix::make(
		      const std::vector<std::vector<int> > &occupied_carriers,
		      int n_syms,
		      const std::string &len_tag_key,
		      const std::string &frame_len_tag_key,
		      const std::string &num_tag_key,
		      int bits_per_header_sym,
		      int bits_per_payload_sym,
		      bool scramble_header)
    {
      return packet_header_ofdm_alix::sptr(
	  new packet_header_ofdm_alix(
	    occupied_carriers, n_syms, len_tag_key, frame_len_tag_key, num_tag_key,
	    bits_per_header_sym, bits_per_payload_sym, scramble_header
	  )
      );
    }

    packet_header_ofdm_alix::packet_header_ofdm_alix(
		    const std::vector<std::vector<int> > &occupied_carriers,
		    int n_syms,
		    const std::string &len_tag_key,
		    const std::string &frame_len_tag_key,
		    const std::string &num_tag_key,
		    int bits_per_header_sym,
		    int bits_per_payload_sym,
		    bool scramble_header
    ) : packet_header_default_alix(
	  _get_header_len_from_occupied_carriers(occupied_carriers, n_syms),
	  len_tag_key,
	  num_tag_key,
	  bits_per_header_sym),
      d_frame_len_tag_key(pmt::string_to_symbol(frame_len_tag_key)),
      d_occupied_carriers(occupied_carriers),
      d_syms_per_set(0),
      d_bits_per_payload_sym(bits_per_payload_sym),
      d_scramble_mask(d_header_len, 0)
    {
      for (unsigned i = 0; i < d_occupied_carriers.size(); i++) {
	d_syms_per_set += d_occupied_carriers[i].size();
      }

      // Init scrambler mask
      if (scramble_header) {
	// These are just random values which already have OK PAPR:
	gr::digital::lfsr shift_reg(0x8a, 0x6f, 7);
	for (int i = 0; i < d_header_len; i++) {
	  for (int k = 0; k < bits_per_header_sym; k++) {
	    d_scramble_mask[i] ^= shift_reg.next_bit() << k;
	  }
	}
      }
    }

    packet_header_ofdm_alix::~packet_header_ofdm_alix()
    {
    }

    bool packet_header_ofdm_alix::header_formatter(long packet_len, unsigned char *out, const std::vector<tag_t> &tags)
    {
      bool ret_val = packet_header_default_alix::header_formatter(packet_len, out, tags);
      for (int i = 0; i < d_header_len; i++) {
      	out[i] ^= d_scramble_mask[i];
      }
      return ret_val;
    }

    bool packet_header_ofdm_alix::header_parser(
	const unsigned char *in,
  int header_length,
	std::vector<tag_t> &tags)
    {
      // std::cout << "/* message */" << d_num_tag_key << '\n';

      std::vector<unsigned char> in_descrambled(header_length, 0);
      for (int i = 0; i < header_length; i++) {
      	in_descrambled[i] = in[i] ^ d_scramble_mask[i];
      }
      if (!packet_header_default_alix::header_parser(&in_descrambled[0], header_length, tags)) {
	return false;
      }
      int packet_len = 0; // # of bytes in this frame
      for (unsigned i = 0; i < tags.size(); i++) {
	if (pmt::equal(tags[i].key, d_len_tag_key)) {
	  // Convert bytes to complex symbols:
	  packet_len = pmt::to_long(tags[i].value) * 8 / d_bits_per_payload_sym;
	  if (pmt::to_long(tags[i].value) * 8 % d_bits_per_payload_sym) {
	    packet_len++;
	  }
	  tags[i].value = pmt::from_long(packet_len);
	  break;
	}
      }

      // frame_len == # of OFDM symbols in this frame
      int frame_len = packet_len / d_syms_per_set;
      int k = 0;
      int i = frame_len * d_syms_per_set;
      while (i < packet_len) {
	frame_len++;
	i += header_length; //d_occupied_carriers[k].size(); //header_length;
      }
      tag_t tag;
      tag.key = d_frame_len_tag_key;
      tag.value = pmt::from_long(frame_len);
      tags.push_back(tag);

      return true;
    }


  } /* namespace ofdm_allocator */
} /* namespace gr */
