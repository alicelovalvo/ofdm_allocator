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

#ifndef INCLUDED_OFDM_ALLOCATOR_CRC_ALIX_IMPL_H
#define INCLUDED_OFDM_ALLOCATOR_CRC_ALIX_IMPL_H

#include <ofdm_allocator/crc_alix.h>
#include <boost/crc.hpp>

namespace gr {
  namespace ofdm_allocator {

    class crc_alix_impl : public crc_alix
    {
     private:
      bool d_check;
      bool d_packed;
      boost::crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true>    d_crc_impl;
      int d_crc_length;
      char *d_unpacked_crc;
      // Nothing to declare in this block.

     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      crc_alix_impl(bool check, const std::string& lengthtagname, bool packed);
      ~crc_alix_impl();

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

      uint64_t d_npass;
      uint64_t d_nfail;
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_CRC_ALIX_IMPL_H */
