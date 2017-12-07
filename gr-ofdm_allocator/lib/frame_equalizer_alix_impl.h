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

#ifndef INCLUDED_OFDM_ALLOCATOR_FRAME_EQUALIZER_ALIX_IMPL_H
#define INCLUDED_OFDM_ALLOCATOR_FRAME_EQUALIZER_ALIX_IMPL_H

#include <ofdm_allocator/frame_equalizer_alix.h>

namespace gr {
  namespace ofdm_allocator {

    class frame_equalizer_alix_impl : public frame_equalizer_alix
    {
     private:
       const int d_fft_len;
       const int d_cp_len;
       ofdm_equalizer_base_alix::sptr d_eq;
       bool d_propagate_channel_state;
       const int d_fixed_frame_len;
       std::vector<gr_complex> d_channel_state;
       // Nothing to declare in this block.

     protected:
       void parse_length_tags(
    const std::vector<std::vector<tag_t> > &tags,
    gr_vector_int &n_input_items_reqd
       );
      // int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      frame_equalizer_alix_impl(
        ofdm_equalizer_base_alix::sptr equalizer,
        int vector_len,
        int cp_len,
        const std::string &tsb_key,
        bool propagate_channel_state,
        int fixed_frame_len
      );
      ~frame_equalizer_alix_impl();

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_FRAME_EQUALIZER_ALIX_IMPL_H */
