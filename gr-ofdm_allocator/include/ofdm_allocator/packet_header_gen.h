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


#ifndef INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_GEN_H
#define INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_GEN_H

#include <ofdm_allocator/api.h>
#include <gnuradio/tagged_stream_block.h>
#include <ofdm_allocator/packet_header_default_alix.h>


namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API packet_header_gen : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<packet_header_gen> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::packet_header_gen.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::packet_header_gen's
       * constructor is in a private implementation
       * class. ofdm_allocator::packet_header_gen::make is the public interface for
       * creating new instances.
       */
       static sptr make(
       const packet_header_default_alix::sptr &header_formatter,
       int max_len_data_subcarr, int max_len_pilot_subcarr,
       int max_vector_data_subcarr, int max_vector_pilot_subcarr,
       bool fixed_pilot,
       int vector_len,
       const std::string &len_tag_key="packet_len"
       );

       /* \param header_len If this value is given, a packet_header_default
        *                   object is used to generate the header. This is
        *                   the number of bits per header.
        * \param len_tag_key Length tag key.
        */
       static sptr make(
       long header_len,
       int max_len_data_subcarr, int max_len_pilot_subcarr,
       int max_vector_data_subcarr, int max_vector_pilot_subcarr,
       bool fixed_pilot,
       int vector_len,
       const std::string &len_tag_key = "packet_len");

       virtual void set_header_formatter(packet_header_default_alix::sptr header_formatter)=0;
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_PACKET_HEADER_GEN_H */
