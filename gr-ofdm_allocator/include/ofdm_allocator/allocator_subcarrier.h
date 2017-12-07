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


#ifndef INCLUDED_OFDM_ALLOCATOR_ALLOCATOR_SUBCARRIER_H
#define INCLUDED_OFDM_ALLOCATOR_ALLOCATOR_SUBCARRIER_H

#include <ofdm_allocator/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API allocator_subcarrier : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<allocator_subcarrier> sptr;

      virtual std::string len_tag_key() = 0;
      virtual const int fft_len() = 0;
      // virtual std::vector<std::vector<int> > occupied_carriers() = 0;


      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::allocator_subcarrier.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::allocator_subcarrier's
       * constructor is in a private implementation
       * class. ofdm_allocator::allocator_subcarrier::make is the public interface for
       * creating new instances.
       */
      static sptr make(
        int fft_len,
        int vector_len,
    	  // const std::vector<std::vector<int> > &occupied_carriers,
    	  const std::vector<std::vector<int> > &pilot_carriers,
    	  const std::vector<std::vector<gr_complex> > &pilot_symbols,
    	  const std::vector<std::vector<gr_complex> > &sync_words,
    	  const std::string &len_tag_key = "packet_len",
    	  const bool output_is_shifted=true
      );

    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_ALLOCATOR_SUBCARRIER_H */
