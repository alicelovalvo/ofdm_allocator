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
#include <iostream>
#include <ofdm_allocator/ofdm_equalizer_simpledfe_alix.h>

namespace gr {
  namespace ofdm_allocator {

    ofdm_equalizer_simpledfe_alix::sptr
    ofdm_equalizer_simpledfe_alix::make(
	  int fft_len,
	  const gr::ofdm_allocator::constellation_alix_sptr &constellation,
	  const std::vector<std::vector<int> > &occupied_carriers,
	  const std::vector<std::vector<int> > &pilot_carriers,
	  const std::vector<std::vector<gr_complex> > &pilot_symbols,
	  int symbols_skipped,
	  float alpha,
	  bool input_is_shifted)
    {
      return ofdm_equalizer_simpledfe_alix::sptr(
	  new ofdm_equalizer_simpledfe_alix(
	      fft_len,
	      constellation,
	      occupied_carriers,
	      pilot_carriers,
	      pilot_symbols,
	      symbols_skipped,
	      alpha,
	      input_is_shifted
	  )
      );
    }

    ofdm_equalizer_simpledfe_alix::ofdm_equalizer_simpledfe_alix(
	int fft_len,
	const gr::ofdm_allocator::constellation_alix_sptr &constellation,
	const std::vector<std::vector<int> > &occupied_carriers,
	const std::vector<std::vector<int> > &pilot_carriers,
	const std::vector<std::vector<gr_complex> > &pilot_symbols,
	int symbols_skipped,
	float alpha,
	bool input_is_shifted)
      : ofdm_equalizer_1d_pilots_alix(fft_len, occupied_carriers, pilot_carriers, pilot_symbols, symbols_skipped, input_is_shifted),
    d_constellation(constellation),
	  d_alpha(alpha)
    {
    }


    ofdm_equalizer_simpledfe_alix::~ofdm_equalizer_simpledfe_alix()
    {
    }

    void
    ofdm_equalizer_simpledfe_alix::equalize(gr_complex *frame,
	      int n_sym,
	      const std::vector<gr_complex> &initial_taps,
	      const std::vector<std::vector<bool> > &occupied_carriers,
	      const std::vector<std::vector<bool> > &pilot_carriers,
	      const std::vector<std::vector<gr_complex> > &pilot_symbols,
	      const std::vector<tag_t> &tags)
    {
      if (!initial_taps.empty()) {
	d_channel_state = initial_taps;
      }
      gr_complex sym_eq, sym_est;

      std::cout << "/* message */" << d_data_carr_set << '\n';
      std::cout << "/* size */" << occupied_carriers.size() << '\n';
      for (int i = 0; i < n_sym; i++) {
	for (int k = 0; k < d_fft_len; k++) {
	  if (!occupied_carriers[d_data_carr_set][k]) {
	    continue;
	  }
	  if (!pilot_carriers.empty() && pilot_carriers[d_pilot_carr_set][k]) {
	    d_channel_state[k] = d_alpha * d_channel_state[k]
			       + (1-d_alpha) * frame[i*d_fft_len + k] / pilot_symbols[d_pilot_carr_set][k];
	    frame[i*d_fft_len+k] = pilot_symbols[d_pilot_carr_set][k];
	  } else {
	    sym_eq = frame[i*d_fft_len+k] / d_channel_state[k];
            // The `map_to_points` function will treat `sym_est` as an array
            // pointer.  This call is "safe" because `map_to_points` is limited
            // by the dimensionality of the constellation. This class calls the
            // `constellation` class default constructor, which initializes the
            // dimensionality value to `1`. Thus, Only the single `gr_complex`
            // value will be dereferenced.
	    d_constellation->map_to_points(d_constellation->decision_maker(&sym_eq), &sym_est);
	    d_channel_state[k] = d_alpha * d_channel_state[k]
                               + (1-d_alpha) * frame[i*d_fft_len + k] / sym_est;
	    frame[i*d_fft_len+k] = sym_est;
	  }
	}
  if (!occupied_carriers.empty()) {
	  d_data_carr_set = (d_data_carr_set + 1) % occupied_carriers.size();
	}
	if (!pilot_carriers.empty()) {
	  d_pilot_carr_set = (d_pilot_carr_set + 1) % pilot_carriers.size();
	}
      }
    }
  } /* namespace ofdm_allocator */
} /* namespace gr */
