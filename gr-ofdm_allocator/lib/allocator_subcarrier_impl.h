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

#ifndef INCLUDED_OFDM_ALLOCATOR_ALLOCATOR_SUBCARRIER_IMPL_H
#define INCLUDED_OFDM_ALLOCATOR_ALLOCATOR_SUBCARRIER_IMPL_H

#include <ofdm_allocator/allocator_subcarrier.h>

namespace gr {
  namespace ofdm_allocator {

    class allocator_subcarrier_impl : public allocator_subcarrier
    {
     private:
       //! FFT length
       const int d_fft_len;
       // const int d_vector_len;
       //! Which carriers/symbols carry data
       // std::vector<std::vector<int> > d_occupied_carriers;
       //! Which carriers/symbols carry pilots symbols
       std::vector<std::vector<int> > d_pilot_carriers;
       //! Value of said pilot symbols
       const std::vector<std::vector<gr_complex> > d_pilot_symbols;
       //! Synch words
       const std::vector<std::vector<gr_complex> > d_sync_words;
       int d_data_sub;
       int d_pilot_sub;
       int d_vector_data;
       int d_vector_pilot;
       bool d_fixed_data;
       bool d_fixed_pilot;
       int d_symbols_per_set;
       const bool d_output_is_shifted;


     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);


     public:
      allocator_subcarrier_impl(
        int fft_len,
        int vector_len,
        bool fixed_data, bool fixed_pilot,
        int max_len_data_subcarr, int max_len_pilot_subcarr,
        int max_vector_data_subcarr, int max_vector_pilot_subcarr,
    	  // const std::vector<std::vector<int> > &occupied_carriers,
    	  const std::vector<std::vector<int> > &pilot_carriers,
    	  const std::vector<std::vector<gr_complex> > &pilot_symbols,
    	  const std::vector<std::vector<gr_complex> > &sync_words,
    	  const std::string &len_tag_key,
    	  const bool output_is_shifted
      );
      ~allocator_subcarrier_impl();


      std::string len_tag_key() { return d_length_tag_key_str; };


      const int fft_len() { return d_fft_len; };
      // std::vector<std::vector<int> > occupied_carriers() { return d_occupied_carriers; };

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_ALLOCATOR_SUBCARRIER_IMPL_H */
