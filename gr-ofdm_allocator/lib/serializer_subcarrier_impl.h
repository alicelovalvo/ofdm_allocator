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

#ifndef INCLUDED_OFDM_ALLOCATOR_SERIALIZER_SUBCARRIER_IMPL_H
#define INCLUDED_OFDM_ALLOCATOR_SERIALIZER_SUBCARRIER_IMPL_H

#include <ofdm_allocator/serializer_subcarrier.h>

namespace gr {
  namespace ofdm_allocator {

    class serializer_subcarrier_impl : public serializer_subcarrier
    {
     private:
       int d_fft_len; //!< FFT length
       pmt::pmt_t d_packet_len_tag_key; //!< Key of the length tag
       pmt::pmt_t d_out_len_tag_key; //!< Key of the length tag
       const int d_symbols_skipped; //!< Start position in d_occupied_carriers
       pmt::pmt_t d_carr_offset_key; //!< Key of the carrier offset tag
       int d_curr_set; //!< Current position in d_occupied_carriers
       int d_symbols_per_set;
        bool d_fixed_pilot;
        bool d_fixed_data;
        int d_pilot_sub;
        int d_vector_pilot;
        int d_data_sub;
        int d_vector_data;
       int d_input_is_shifted;

     protected:
       int calculate_output_stream_length(const gr_vector_int &ninput_items);
       void update_length_tags(int n_produced, int n_ports);

     public:
      serializer_subcarrier_impl(
	  int fft_len,
    int vector_len,
      bool fixed_pilot,
      bool fixed_data,
      int max_len_data_subcarr, int max_len_pilot_subcarr,
      int max_vector_data_subcarr, int max_vector_pilot_subcarr,
	  const std::string &len_tag_key,
	  const std::string &packet_len_tag_key,
	  int symbols_skipped,
	  const std::string &carr_offset_key,
	  bool input_is_shifted);
      ~serializer_subcarrier_impl();

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_SERIALIZER_SUBCARRIER_IMPL_H */
