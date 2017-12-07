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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "allocator_subcarrier_impl.h"
#include <string.h>
#include <iostream>
#include <iomanip>

namespace gr {
  namespace ofdm_allocator {

    allocator_subcarrier::sptr
    allocator_subcarrier::make(
  int fft_len,
  int vector_len,
	const std::vector<std::vector<int> > &pilot_carriers,
	const std::vector<std::vector<gr_complex> > &pilot_symbols,
	const std::vector<std::vector<gr_complex> > &sync_words,
	const std::string &len_tag_key,
	const bool output_is_shifted
    )
    {
      return gnuradio::get_initial_sptr(
    new allocator_subcarrier_impl(
     fft_len,
     vector_len,
     pilot_carriers,
     pilot_symbols,
     sync_words,
     len_tag_key,
     output_is_shifted
        )
      );
    }

    /*
     * The private constructor
     */
    allocator_subcarrier_impl::allocator_subcarrier_impl(
   int fft_len,
   int vector_len,
   const std::vector<std::vector<int> > &pilot_carriers,
   const std::vector<std::vector<gr_complex> > &pilot_symbols,
   const std::vector<std::vector<gr_complex> > &sync_words,
   const std::string &len_tag_key,
   const bool output_is_shifted
    )
      : gr::tagged_stream_block("allocator_subcarrier",
              gr::io_signature::make2(2, 2, sizeof(gr_complex), sizeof(int)*vector_len),
              gr::io_signature::make(1, 1, sizeof(gr_complex) * fft_len), len_tag_key),
    d_fft_len(fft_len),
    // d_vector_len(vector_len),
    d_pilot_carriers(pilot_carriers),
    d_pilot_symbols(pilot_symbols),
    d_sync_words(sync_words),
    d_symbols_per_set(0),
    d_output_is_shifted(output_is_shifted)
    {
  //     for (unsigned i = 0; i < d_occupied_carriers.size(); i++) {
	// for (unsigned j = 0; j < d_occupied_carriers[i].size(); j++) {
  //
	//   if (occupied_carriers[i][j] < 0) {
	//     d_occupied_carriers[i][j] += d_fft_len;
	//   }
	//   if (d_occupied_carriers[i][j] > d_fft_len || d_occupied_carriers[i][j] < 0) {
	//     throw std::invalid_argument("data carrier index out of bounds");
	//   }
	//   if (d_output_is_shifted) {
	//     d_occupied_carriers[i][j] = (d_occupied_carriers[i][j] + fft_len/2) % fft_len;
	//   }
	// }
  //     }
      for (unsigned i = 0; i < d_pilot_carriers.size(); i++) {
	for (unsigned j = 0; j < d_pilot_carriers[i].size(); j++) {
	  if (d_pilot_carriers[i][j] < 0) {
	    d_pilot_carriers[i][j] += d_fft_len;
	  }
	  if (d_pilot_carriers[i][j] > d_fft_len || d_pilot_carriers[i][j] < 0) {
	    throw std::invalid_argument("pilot carrier index out of bounds");
	  }
	  if (d_output_is_shifted) {
	    d_pilot_carriers[i][j] = (d_pilot_carriers[i][j] + fft_len/2) % fft_len;
	  }
	}
      }
      for (unsigned i = 0; i < std::max(d_pilot_carriers.size(), d_pilot_symbols.size()); i++) {
	if (d_pilot_carriers[i % d_pilot_carriers.size()].size() != d_pilot_symbols[i % d_pilot_symbols.size()].size()) {
	  throw std::invalid_argument("pilot_carriers do not match pilot_symbols");
	}
      }
      for (unsigned i = 0; i < d_sync_words.size(); i++) {
	if (d_sync_words[i].size() != (unsigned) d_fft_len) {
	  throw std::invalid_argument("sync words must be fft length");
	}
      }

  //     for (unsigned i = 0; i < d_occupied_carriers.size(); i++) {
	// d_symbols_per_set += d_occupied_carriers[i].size();
  //     }
  //     set_tag_propagation_policy(TPP_DONT);
  //     set_relative_rate((double) d_symbols_per_set / d_occupied_carriers.size());
    }

    /*
     * Our virtual destructor.
     */
    allocator_subcarrier_impl::~allocator_subcarrier_impl()
    {
    }

    int
    allocator_subcarrier_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      // int nin = ninput_items[0];
      // int nout = (nin / d_symbols_per_set) * d_occupied_carriers.size();
      // int k = 0;
  //     for (int i = 0; i < nin % d_symbols_per_set; k++) {
	// nout++;
	// i += d_occupied_carriers[k % d_occupied_carriers.size()].size();
  //     }
      // return nout + d_sync_words.size();
      int nout = 0;
  //     for (unsigned i = 0; i < ninput_items.size(); i++) {
	// nout += ninput_items[i];
  //     }
      return nout;
        }

    int
    allocator_subcarrier_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      int *in2 = (int *) input_items[1];
      gr_complex *out = (gr_complex *) output_items[0];
      std::vector<tag_t> tags;

      set_relative_rate(ninput_items.size());

	    // get_tags_in_range(tags, 1, nitems_read(1), nitems_read(1)+ninput_items[1]);

      memset((void *) out, 0x00, sizeof(gr_complex) * d_fft_len * noutput_items);


        d_symbols_per_set = 0;

      // Copy Sync word
      for (unsigned i = 0; i < d_sync_words.size(); i++) {
	       memcpy((void *) out, (void *) &d_sync_words[i][0], sizeof(gr_complex) * d_fft_len);
	       out += d_fft_len;
      }
      // std::cout << "in2";
      // for(int i=0; i<ninput_items[1]; i++){
      //
      //   std::cout << in2[i] << ", ";
      // }
      // std::cout << '\n';
      std::vector<int> vector_sub;
      std::vector<std::vector<int> > vector_vector_sub;

      // std::cout << ninput_items[1] <<"/* message */" << '\n';

        for (int i=0; i< (ninput_items[1]/48); i++){
          // std::cout << "in2 : " ;
         for(int j=0; j < 48; j++){
           int cycle = i*48;
           if (in2[j+cycle] == 0){
             continue;
          }
          else{
           if(in2[j+cycle] < 0){
             in2[j+cycle] += d_fft_len;
           }
           if (in2[j+cycle] > d_fft_len || in2[j+cycle] < 0) {
             throw std::invalid_argument("data carrier index out of bounds");
           }
           if (d_output_is_shifted) {
             in2[j+cycle] = (in2[j+cycle] + d_fft_len/2) % d_fft_len;
           }
        //   std::cout << "j: " <<j << '\n';
        //  // for(int i=0; i < in2[j].size(); i++){
           // std::cout << in2[j+cycle] - 32 <<", ";
        //   // }
          // std::fill (vector_sub.begin()+j,vector_sub.begin()+j+1,in2[j]);
          vector_sub.push_back(in2[j+cycle]);
          }
        }
        if (vector_sub.size()!=0){
          vector_vector_sub.push_back(vector_sub);
          // std::cout << "##############################" << '\n';
          vector_sub.erase(vector_sub.begin(),vector_sub.end());
        }
      }
      // for (int l=0; l<vector_vector_sub.size();l++){
      //   // std::cout << "/* in2_vector: */";
      //   for (int i=0; i<vector_vector_sub[l].size(); i++){
      //     std::cout << vector_vector_sub[l][i] - 32 << ", ";
      //   }
      //   // std::cout << '\n';
      // }
        //std::cout << "/* vector_sub */" << vector_sub.size() << '\n';
        //for (int i=0; i < vector_sub.size(); i++){
        //  std::cout << vector_sub[i] - 32 << ", ";
        //}
      // std::cout << "size : ";
      // std::cout << ninput_items[1];
      //std::cout <<'\n';
      // }
      // Copy data symbols
      long n_ofdm_symbols = 0; // Number of output items
      int curr_set = 0;
      // int symbols_to_allocate = d_occupied_carriers[0].size();
      int symbols_to_allocate = vector_vector_sub[0].size();
      int symbols_allocated = 0;
      std::cout << '\n' << "####### allocator ######" << '\n';

      for (int i = 0; i < ninput_items[0]; i++) {

	if (symbols_allocated == 0) {
    std::cout << "active_subcarrier : ";

      // std::cout << "d_occupied_carriers " << n_ofdm_symbols <<':';
// std::cout << "/* tags.size() */" << tags.size() << '\n';
	  // Copy all tags associated with these input symbols onto this OFDM symbol
	  get_tags_in_range(tags, 0,
	      nitems_read(0)+i,
	      nitems_read(0)+std::min(i+symbols_to_allocate, (int) ninput_items[0])
	  );
    // std::cout << "/* tags */" << tags[0] << '\n';
    // std::cout << "/* nitems_written */" << nitems_written(0) <<'\n';
    // std::cout << "/* noutput_items_allocator */" << noutput_items << '\n';

    for (unsigned t = 0; t < tags.size(); t++) {
      // std::cout << "/* tag */" << tags[t].key << '\n';
	    add_item_tag(
		0,
		nitems_written(0) + n_ofdm_symbols + (n_ofdm_symbols == 0 ? 0 : d_sync_words.size()),
		tags[t].key,
		tags[t].value
	    );
	  }
	  n_ofdm_symbols++;
	}
  // int subcarrier = (n_ofdm_symbols-1) * d_fft_len + d_occupied_carriers[curr_set][symbols_allocated];
  // std::cout << "n_ofdm_symbols : " << n_ofdm_symbols << std::endl;
  // std::cout << "curr_set : " << curr_set << std::endl;
  // std::cout << "symbols_allocated : " << symbols_allocated << std::endl;
  // std::cout << "subcarrier : " << subcarrier << std::endl;
  // std::cout << "symbols_to_allocate : " << symbols_to_allocate << std::endl;
  // out[(n_ofdm_symbols-1) * d_fft_len + d_occupied_carriers[curr_set][symbols_allocated]] = in[i];
  out[(n_ofdm_symbols-1) * d_fft_len + vector_vector_sub[curr_set][symbols_allocated]] = in[i];

   //std::cout << "in : " << vector_sub[symbols_allocated] - 32 << ',';
  std::cout << (vector_vector_sub[curr_set][symbols_allocated] - 32) << ',';

	symbols_allocated++;
	if (symbols_allocated == symbols_to_allocate) {
	  curr_set = (curr_set + 1) % vector_vector_sub.size();
	  symbols_to_allocate = vector_vector_sub[curr_set].size();
    // symbols_to_allocate = vector_sub.size();
    //   std::cout << "d_occupied_carriers " << n_ofdm_symbols <<':';
    // for (int i = 0; i < d_occupied_carriers[curr_set].size(); i++){
    //   std::cout << (d_occupied_carriers[curr_set][i] - 32) << ',';
    // }
    std::cout << '\n';
	  symbols_allocated = 0;
	}
  if (i == (ninput_items[0]-1)){
    std::cout << '\n' << "####### end allocator ######" << '\n';
  }
}
      // Copy pilot symbols
      for (int i = 0; i < n_ofdm_symbols; i++) {
	for (unsigned k = 0; k < d_pilot_carriers[i % d_pilot_carriers.size()].size(); k++) {
	  out[i * d_fft_len + d_pilot_carriers[i % d_pilot_carriers.size()][k]] = d_pilot_symbols[i % d_pilot_symbols.size()][k];
	}
      }

      d_symbols_per_set = ninput_items[1];
      set_tag_propagation_policy(TPP_DONT);
      // set_relative_rate((double) d_symbols_per_set);
      set_relative_rate((double) d_symbols_per_set / vector_vector_sub.size());

      // std::cout << '\n';

      return n_ofdm_symbols + d_sync_words.size();

    }

  } /* namespace ofdm_allocator */
} /* namespace gr */
