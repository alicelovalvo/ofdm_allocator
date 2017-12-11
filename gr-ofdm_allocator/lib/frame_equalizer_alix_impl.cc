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

#include <gnuradio/expj.h>
#include <gnuradio/io_signature.h>
#include "frame_equalizer_alix_impl.h"

#define M_TWOPI (2*M_PI)

static const pmt::pmt_t CARR_OFFSET_KEY = pmt::mp("ofdm_sync_carr_offset");
static const pmt::pmt_t CHAN_TAPS_KEY = pmt::mp("ofdm_sync_chan_taps");

namespace gr {
  namespace ofdm_allocator {

    frame_equalizer_alix::sptr
    frame_equalizer_alix::make(
      ofdm_equalizer_base_alix::sptr equalizer,
      int vector_len,
      int cp_len,
      bool fixed_pilot,
      bool fixed_data,
      int max_len_data_subcarr, int max_len_pilot_subcarr,
      int max_vector_data_subcarr, int max_vector_pilot_subcarr,
      const std::vector<std::vector<gr_complex> > &pilot_symbols,
      const std::string &tsb_key,
      bool propagate_channel_state,
      int fixed_frame_len,
      bool input_is_shifted
    )
    {
      return gnuradio::get_initial_sptr
        (new frame_equalizer_alix_impl(
    	    equalizer, vector_len, cp_len, fixed_pilot, fixed_data, max_len_data_subcarr, max_len_pilot_subcarr, max_vector_data_subcarr, max_vector_pilot_subcarr, pilot_symbols, tsb_key, propagate_channel_state, fixed_frame_len, input_is_shifted));
    }

    /*
     * The private constructor
     */
    frame_equalizer_alix_impl::frame_equalizer_alix_impl(
      ofdm_equalizer_base_alix::sptr equalizer,
      int vector_len,
      int cp_len,
      bool fixed_pilot,
      bool fixed_data,
      int max_len_data_subcarr, int max_len_pilot_subcarr,
      int max_vector_data_subcarr, int max_vector_pilot_subcarr,
      const std::vector<std::vector<gr_complex> > &pilot_symbols,
      const std::string &tsb_key,
      bool propagate_channel_state,
      int fixed_frame_len,
      bool input_is_shifted
    )
      : gr::tagged_stream_block("frame_equalizer_alix",
              // gr::io_signature::make(1, 1, sizeof (gr_complex) * equalizer->fft_len()),
              gr::io_signature::make2(2, 2, sizeof (gr_complex) * equalizer->fft_len(), sizeof(int)*vector_len),
              gr::io_signature::make(1, 1, sizeof (gr_complex) * equalizer->fft_len()),
              tsb_key),
        d_fft_len(equalizer->fft_len()),
        d_cp_len(cp_len),
        d_eq(equalizer),
        d_input_is_shifted(input_is_shifted),
        d_fixed_pilot(fixed_pilot),
	d_fixed_data(fixed_data),
        d_pilot_sub(max_len_pilot_subcarr),
        d_vector_pilot(max_vector_pilot_subcarr),
        d_data_sub(max_len_data_subcarr),
	d_vector_data(max_vector_data_subcarr),
	d_pilot_symbols_input(pilot_symbols),
	d_pilot_symbols(pilot_symbols.size(), std::vector<gr_complex>(d_fft_len, gr_complex(0, 0))),
        d_propagate_channel_state(propagate_channel_state),
        d_fixed_frame_len(fixed_frame_len),
        d_channel_state(equalizer->fft_len(), gr_complex(1, 0))
    {
      if (tsb_key.empty() && fixed_frame_len == 0) {
        throw std::invalid_argument("Either specify a TSB tag or a fixed frame length!");
      }
      if (d_fixed_frame_len < 0) {
        throw std::invalid_argument("Invalid frame length!");
      }
      if (d_fixed_frame_len) {
        set_output_multiple(d_fixed_frame_len);
      }
      set_relative_rate(1.0);
      // Really, we have TPP_ONE_TO_ONE, but the channel state is not propagated
      set_tag_propagation_policy(TPP_DONT);
    }

    /*
     * Our virtual destructor.
     */
    frame_equalizer_alix_impl::~frame_equalizer_alix_impl()
    {
    }

    void
    frame_equalizer_alix_impl::parse_length_tags(
        const std::vector<std::vector<tag_t> > &tags,
        gr_vector_int &n_input_items_reqd
    ) {
      if (d_fixed_frame_len) {
        n_input_items_reqd[0] = d_fixed_frame_len;
        for (unsigned k = 0; k < tags[1].size(); k++) {
          if (tags[1][k].key == pmt::string_to_symbol(d_length_tag_key_str)) {
            n_input_items_reqd[1] = pmt::to_long(tags[1][k].value);
		remove_item_tag(1, tags[1][k]);
          }
        }      } else {
        for (unsigned k = 0; k < tags[0].size(); k++) {
          if (tags[0][k].key == pmt::string_to_symbol(d_length_tag_key_str)) {
            n_input_items_reqd[0] = pmt::to_long(tags[0][k].value);
          }
        }
        for (unsigned k = 0; k < tags[1].size(); k++) {
          if (tags[1][k].key == pmt::string_to_symbol(d_length_tag_key_str)) {
            n_input_items_reqd[1] = pmt::to_long(tags[1][k].value);
	remove_item_tag(1, tags[1][k]);
          }
        }
      }
    }

    int
    frame_equalizer_alix_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      int *in2 = (int *) input_items[1];
      gr_complex *out = (gr_complex *) output_items[0];
      int carrier_offset = 0;
      int frame_len = 0;
      if (d_fixed_frame_len) {
	frame_len = d_fixed_frame_len;
      } else {
	frame_len = ninput_items[0];
      }
      std::vector<tag_t> tags;
      get_tags_in_window(tags, 0, 0, 1);
      for (unsigned i = 0; i < tags.size(); i++) {
        if (pmt::symbol_to_string(tags[i].key) == "ofdm_sync_chan_taps") {
          d_channel_state = pmt::c32vector_elements(tags[i].value);
        }
        if (pmt::symbol_to_string(tags[i].key) == "ofdm_sync_carr_offset") {
          carrier_offset = pmt::to_long(tags[i].value);
        }
      }
      // ***************************************************** //
      std::vector<bool> data_carriers(d_fft_len, false);
      std::vector<int> vector_sub;
      std::vector<int> vector_sub_pilot;
      std::vector<std::vector<int> > vector_vector_sub;
      std::vector<std::vector<int> > vector_vector_sub_pilot;
       int fft_shift_width = 0;
       int interval = (ninput_items[1]-d_pilot_sub)/d_data_sub;
       if (!d_fixed_pilot){
         interval = (ninput_items[1]-(d_pilot_sub*d_vector_pilot))/d_data_sub;
       }
	std::cout << "ninput: " << ninput_items[1] << '\n';
	std::cout << "interval" << interval << '\n';
      if (d_input_is_shifted) {
        fft_shift_width = d_fft_len/2;
      }
      // if (!occupied_carriers.size()) {
	//TODO: sistemare questo controllo -non proprio corretto
      if (!ninput_items[1]){
          std::fill(data_carriers.begin(), data_carriers.end(), true);
        // }
        //   std::fill(d_occupied_carriers.begin(), d_occupied_carriers.end(), true);
      } else {
        for (int i=0; i< interval; i++){
           std::cout << i << " in2 aaaa: " ;
          for(int j=0; j < d_data_sub; j++){
            int cycle = i*d_data_sub;
            if (in2[j+cycle] == 0){
              continue;
            }
            else{

              //   std::cout << "j: " <<j << '\n';
              //  // for(int i=0; i < in2[j].size(); i++){
               std::cout << in2[j+cycle]  <<", ";
              //   // }
              // std::fill (vector_sub.begin()+j,vector_sub.begin()+j+1,in2[j]);
              vector_sub.push_back(in2[j+cycle]);
            }
          }
	std::cout << '\n';
          if (vector_sub.size()!=0){
            vector_vector_sub.push_back(vector_sub);
            // std::cout << "##############################" << '\n';
            vector_sub.erase(vector_sub.begin(),vector_sub.end());
          }
        }

        for (unsigned i = 0; i < vector_vector_sub.size(); i++) {
          for (unsigned k = 0; k < vector_vector_sub[i].size(); k++) {
            int carr_index = vector_vector_sub[i][k];
            if (vector_vector_sub[i][k] < 0) {
              carr_index += d_fft_len;
            }
            if (carr_index >= d_fft_len || carr_index < 0) {
              throw std::invalid_argument("data carrier index out of bounds.");
            }
            data_carriers[(carr_index + fft_shift_width) % d_fft_len] = true;
          }
        }
      }
	// std::cout << "data_carriers: ";
	// for(int i=0; i<data_carriers.size(); i++){
	// std::cout << data_carriers[i] << ", ";
  //
	// }
	// std::cout << '\n';
      int interval_pilot = (ninput_items[1]-d_data_sub)/d_pilot_sub;;
      if (!d_fixed_data){
         interval_pilot = (ninput_items[1]-(d_data_sub*d_vector_data))/d_pilot_sub;
       }
      std::vector<std::vector<bool> > pilot_carriers(interval_pilot, std::vector<bool>(d_fft_len, false));

      //TODO: sistemare questo controllo -non proprio corretto
      if (ninput_items[1]) {
        for (unsigned i = 0; i < interval_pilot; i++) {
	// std::cout << "in2 pilot aaa: ";
	for(int j=0; j < d_pilot_sub; j++){
            int cycle = i*d_pilot_sub;
            if (in2[j+cycle+(d_data_sub*d_vector_data)] == 0){
              continue;
            }
            else{

//                 std::cout << "j: " <<j << '\n';
                // for(int i=0; i < in2[j].size(); i++){
               // std::cout << in2[j+cycle+(d_data_sub*d_vector_data)] <<", ";
                 // }
              // std::fill (vector_sub.begin()+j,vector_sub.begin()+j+1,in2[j]);
              vector_sub_pilot.push_back(in2[j+cycle+(d_data_sub*d_vector_data)]);
            }
          }
	// std::cout << '\n' << "vector_sub_pilot: ";
	// for(int f=0; f<vector_sub_pilot.size(); f++){
	// 	std::cout << vector_sub_pilot[f] << ", ";
	// }
	// std::cout << '\n';
          if (vector_sub_pilot.size()!=0){
            vector_vector_sub_pilot.push_back(vector_sub_pilot);
            // std::cout << "##############################" << '\n';
            vector_sub_pilot.erase(vector_sub_pilot.begin(),vector_sub_pilot.end());
          }
//	 std::cout << vector_vector_sub_pilot.size() << "size_vector_vector" << '\n';
//	std::cout << vector_vector_sub_pilot[i].size() << "size_vector_i" << '\n';
//	std::cout << d_pilot_symbols_input[i].size() << "size_pilot_symbols" << '\n';
//        }
          if (vector_vector_sub_pilot[i].size() != d_pilot_symbols_input[i].size()) {
            throw std::invalid_argument("pilot carriers and -symbols do not match.");
          }
          for (unsigned k = 0; k < vector_vector_sub_pilot[i].size(); k++) {
            int carr_index = vector_vector_sub_pilot[i][k];
            if (vector_vector_sub_pilot[i][k] < 0) {
              carr_index += d_fft_len;
            }
            if (carr_index >= d_fft_len || carr_index < 0) {
              throw std::invalid_argument("pilot carrier index out of bounds.");
            }
            pilot_carriers[i][(carr_index + 32) % d_fft_len] = true;
            d_pilot_symbols[i][(carr_index + 32) % d_fft_len] = d_pilot_symbols[i][k];
//            pilot_carriers[i][(carr_index + fft_shift_width) % d_fft_len] = true;
//            d_pilot_symbols[i][(carr_index + fft_shift_width) % d_fft_len] = d_pilot_symbols[i][k];
          }
	//         std::cout << "pilot_carriers: ";
  //       for(int i=0; i<pilot_carriers.size(); i++){
	// 	for(int l=0; l<pilot_carriers[i].size(); l++){
  //      std::cout << pilot_carriers[i][l] << ", ";
	// 	}
  //       }
	// std::cout << '\n';
        }
      }

      // *************************************************** //

      // Copy the frame and the channel state vector such that the symbols are shifted to the correct position
      if (carrier_offset < 0) {
	memset((void *) out, 0x00, sizeof(gr_complex) * (-carrier_offset));
	memcpy(
	    (void *) &out[-carrier_offset], (void *) in,
	    sizeof(gr_complex) * (d_fft_len * frame_len + carrier_offset)
	);
      } else {
	memset((void *) (out + d_fft_len * frame_len - carrier_offset), 0x00, sizeof(gr_complex) * carrier_offset);
	memcpy(
	    (void *) out, (void *) (in+carrier_offset),
	    sizeof(gr_complex) * (d_fft_len * frame_len - carrier_offset)
	);
      }

      // Correct the frequency shift on the symbols
      gr_complex phase_correction;
      for (int i = 0; i < frame_len; i++) {
	phase_correction = gr_expj(-M_TWOPI * carrier_offset * d_cp_len / d_fft_len * (i+1));
	for (int k = 0; k < d_fft_len; k++) {
	  out[i*d_fft_len+k] *= phase_correction;
	}
      }

      // Do the equalizing
      d_eq->reset(pilot_carriers);
      d_eq->equalize(out, frame_len, d_channel_state, data_carriers, pilot_carriers, d_pilot_symbols);
      d_eq->get_channel_state(d_channel_state);

      // Update the channel state regarding the frequency offset
      phase_correction = gr_expj(M_TWOPI * carrier_offset * d_cp_len / d_fft_len * frame_len);
      for (int k = 0; k < d_fft_len; k++) {
        d_channel_state[k] *= phase_correction;
      }

      // Propagate tags (except for the channel state and the TSB tag)
      get_tags_in_window(tags, 0, 0, frame_len);
      for (size_t i = 0; i < tags.size(); i++) {
        if (tags[i].key != CHAN_TAPS_KEY
            && tags[i].key != pmt::mp(d_length_tag_key_str)) {
          add_item_tag(0, tags[i]);
        }
      }

      // Housekeeping
      if (d_propagate_channel_state) {
	add_item_tag(0, nitems_written(0),
	    pmt::string_to_symbol("ofdm_sync_chan_taps"),
	    pmt::init_c32vector(d_fft_len, d_channel_state));
      }

      if (d_fixed_frame_len && d_length_tag_key_str.empty()) {
	consume_each(frame_len);
      }

      return frame_len;
    }

  } /* namespace ofdm_allocator */
} /* namespace gr */
