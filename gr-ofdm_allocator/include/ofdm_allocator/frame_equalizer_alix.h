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


#ifndef INCLUDED_OFDM_ALLOCATOR_FRAME_EQUALIZER_ALIX_H
#define INCLUDED_OFDM_ALLOCATOR_FRAME_EQUALIZER_ALIX_H

#include <ofdm_allocator/api.h>
#include <ofdm_allocator/ofdm_equalizer_base_alix.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API frame_equalizer_alix : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<frame_equalizer_alix> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::frame_equalizer_alix.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::frame_equalizer_alix's
       * constructor is in a private implementation
       * class. ofdm_allocator::frame_equalizer_alix::make is the public interface for
       * creating new instances.
       */
       static sptr make(
           ofdm_equalizer_base_alix::sptr equalizer,
           int vector_len,
           int cp_len,
           bool fixed_pilot,
           int max_len_data_subcarr, int max_len_pilot_subcarr,
           int max_vector_pilot_subcarr,
           const std::string &tsb_key="frame_len",
           bool propagate_channel_state=false,
           int fixed_frame_len=0,
           bool input_is_shifted=true
       );    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_FRAME_EQUALIZER_ALIX_H */
