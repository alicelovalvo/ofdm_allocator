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


#ifndef INCLUDED_OFDM_ALLOCATOR_CONSTELLATION_DECODER_ALIX_H
#define INCLUDED_OFDM_ALLOCATOR_CONSTELLATION_DECODER_ALIX_H

#include <ofdm_allocator/api.h>
#include <ofdm_allocator/constellation_alix.h>
#include <gnuradio/block.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API constellation_decoder_alix : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<constellation_decoder_alix> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::constellation_decoder_alix.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::constellation_decoder_alix's
       * constructor is in a private implementation
       * class. ofdm_allocator::constellation_decoder_alix::make is the public interface for
       * creating new instances.
       */
       static sptr make(constellation_alix_sptr constellation);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_CONSTELLATION_DECODER_ALIX_H */
