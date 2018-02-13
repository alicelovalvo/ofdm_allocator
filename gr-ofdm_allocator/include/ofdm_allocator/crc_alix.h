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


#ifndef INCLUDED_OFDM_ALLOCATOR_CRC_ALIX_H
#define INCLUDED_OFDM_ALLOCATOR_CRC_ALIX_H

#include <ofdm_allocator/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API crc_alix : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<crc_alix> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::crc_alix.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::crc_alix's
       * constructor is in a private implementation
       * class. ofdm_allocator::crc_alix::make is the public interface for
       * creating new instances.
       */
      static sptr make(bool check=false, const std::string& lengthtagname="packet_len", bool packed=true);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_CRC_ALIX_H */
