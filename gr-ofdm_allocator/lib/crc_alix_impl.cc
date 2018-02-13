/* -*- c++ -*- */
/*
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
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
#include "crc_alix_impl.h"

namespace gr {
  namespace ofdm_allocator {

    crc_alix::sptr
    crc_alix::make(bool check, const std::string &lengthtagname, bool packed)
    {
      return gnuradio::get_initial_sptr
        (new crc_alix_impl(check, lengthtagname, packed));
    }

    /*
     * The private constructor
     */
    crc_alix_impl::crc_alix_impl(bool check, const std::string &lengthtagname, bool packed)
      : gr::tagged_stream_block("crc_alix",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char)),
              lengthtagname),
    d_check(check), d_packed(packed),
          d_npass(0), d_nfail(0) {
      d_crc_length = 4;
      if (!d_packed) {
        d_crc_length = 32;
        d_unpacked_crc = new char[d_crc_length];
      }
      set_tag_propagation_policy(TPP_DONT);
    }

    /*
     * Our virtual destructor.
     */
    crc_alix_impl::~crc_alix_impl()
    {
      if (!d_packed){
        delete[] d_unpacked_crc;
      }
    }

    int
    crc_alix_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      if (d_check) {
        return ninput_items[0] - d_crc_length;
      } else {
        return ninput_items[0] + d_crc_length;
      }
    }

    int
    crc_alix_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      long packet_length = ninput_items[0];
      int packet_size_diff = d_check ? -d_crc_length : d_crc_length;
      unsigned int crc;

      if (d_check) {
        d_crc_impl.reset();
        d_crc_impl.process_bytes(in, packet_length - d_crc_length);
        crc = d_crc_impl();
        if (d_packed) {
          if (crc != *(unsigned int *) (in + packet_length - d_crc_length)) { // Drop package
            d_nfail++;
            return 0;
          }
        }
        else{
          for(int i=0; i < d_crc_length; i++){
            if(((crc >> i) & 0x1) != *(in + packet_length - d_crc_length + i)) { // Drop package
              d_nfail++;
              return 0;
            }
          }
        }
        d_npass++;
        memcpy((void *) out, (const void *) in, packet_length - d_crc_length);
      } else {
        d_crc_impl.reset();
        d_crc_impl.process_bytes(in, packet_length);
        crc = d_crc_impl();
        memcpy((void *) out, (const void *) in, packet_length);
        if (d_packed) {
          memcpy((void *) (out + packet_length), &crc, d_crc_length); // FIXME big-endian/little-endian, this might be wrong
        }
        else {
          for (int i = 0; i < d_crc_length; i++) { // unpack CRC and store in buffer
            d_unpacked_crc[i] = (crc >> i) & 0x1;
          }
          memcpy((void *) (out + packet_length), (void *) d_unpacked_crc, d_crc_length);
        }
      }

      std::vector <tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + packet_length);
      for (size_t i = 0; i < tags.size(); i++) {
        tags[i].offset -= nitems_read(0);
        if (d_check && tags[i].offset > (unsigned int) (packet_length + packet_size_diff)) {
          tags[i].offset = packet_length - d_crc_length - 1;
        }
        add_item_tag(0, nitems_written(0) + tags[i].offset,
                     tags[i].key,
                     tags[i].value);
      }

      return packet_length + packet_size_diff;
    }

  } /* namespace ofdm_allocator */
} /* namespace gr */
