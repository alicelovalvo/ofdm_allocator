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


#ifndef INCLUDED_OFDM_ALLOCATOR_SERIALIZER_SUBCARRIER_H
#define INCLUDED_OFDM_ALLOCATOR_SERIALIZER_SUBCARRIER_H

#include <ofdm_allocator/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API serializer_subcarrier : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<serializer_subcarrier> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::serializer_subcarrier.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::serializer_subcarrier's
       * constructor is in a private implementation
       * class. ofdm_allocator::serializer_subcarrier::make is the public interface for
       * creating new instances.
       */
      static sptr make(
  	  int fft_len,
      int vector_len,
      bool fixed_pilot=true,
      bool fixed_data=true,
      int max_len_data_subcarr=48, int max_len_pilot_subcarr=4,
      int max_vector_data_subcarr=1, int max_vector_pilot_subcarr=1,
  	  const std::string &len_tag_key="frame_len",
  	  const std::string &packet_len_tag_key="",
  	  int symbols_skipped=0,
  	  const std::string &carr_offset_key="",
  	  bool input_is_shifted=true
      );
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_SERIALIZER_SUBCARRIER_H */
