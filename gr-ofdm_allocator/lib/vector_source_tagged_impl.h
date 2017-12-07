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

#ifndef INCLUDED_OFDM_ALLOCATOR_VECTOR_SOURCE_TAGGED_IMPL_H
#define INCLUDED_OFDM_ALLOCATOR_VECTOR_SOURCE_TAGGED_IMPL_H

#include <ofdm_allocator/vector_source_tagged.h>

namespace gr {
  namespace ofdm_allocator {

    class vector_source_tagged_impl : public vector_source_tagged
    {
     private:
      // Nothing to declare in this block.
      std::vector<int> d_data;
      bool d_repeat;
      bool d_fixed;
      unsigned int d_offset;
      int d_vlen;
      int d_i;
      int d_size;
      pmt::pmt_t d_len_tag_key; //!< Key of length tag
      bool d_settags;
      std::vector<tag_t> d_tags;
      unsigned int d_tagpos;

     public:
      vector_source_tagged_impl(const std::vector<int> &data,
                  bool repeat, int vlen, bool fixed,
                  const std::string &length_tag_key,
                  const std::vector<tag_t> &tags);
      ~vector_source_tagged_impl();

      void rewind() { d_offset=0; }
      void set_data(const std::vector<int> &data,
                    const std::vector<tag_t> &tags);

      void set_random_vector();
      void set_repeat(bool repeat) { d_repeat=repeat; };

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_VECTOR_SOURCE_TAGGED_IMPL_H */
