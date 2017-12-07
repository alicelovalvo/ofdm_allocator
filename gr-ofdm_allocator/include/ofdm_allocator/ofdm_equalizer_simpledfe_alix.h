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


#ifndef INCLUDED_OFDM_ALLOCATOR_OFDM_EQUALIZER_SIMPLEDFE_ALIX_H
#define INCLUDED_OFDM_ALLOCATOR_OFDM_EQUALIZER_SIMPLEDFE_ALIX_H

#include <ofdm_allocator/api.h>
#include <ofdm_allocator/constellation_alix.h>
#include <ofdm_allocator/ofdm_equalizer_base_alix.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description+>
     *
     */
    class OFDM_ALLOCATOR_API ofdm_equalizer_simpledfe_alix : public ofdm_equalizer_1d_pilots_alix
    {
    public:
      typedef boost::shared_ptr<ofdm_equalizer_simpledfe_alix> sptr;

      ofdm_equalizer_simpledfe_alix(
	  int fft_len,
	  const gr::ofdm_allocator::constellation_alix_sptr &constellation,
	  const std::vector<std::vector<int> > &occupied_carriers = std::vector<std::vector<int> >(),
	  const std::vector<std::vector<int> > &pilot_carriers = std::vector<std::vector<int> >(),
	  const std::vector<std::vector<gr_complex> > &pilot_symbols = std::vector<std::vector<gr_complex> >(),
	  int symbols_skipped = 0,
	  float alpha = 0.1,
	  bool input_is_shifted = true);

      ~ofdm_equalizer_simpledfe_alix();

      void equalize(gr_complex *frame,
		      int n_sym,
		      const std::vector<gr_complex> &initial_taps = std::vector<gr_complex>(),
		      const std::vector<tag_t> &tags = std::vector<tag_t>());//,
          // const std::vector<bool> occupied_carriers = std::vector<bool> ());


      // float get_distance(unsigned int index, const gr_complex *sample);
      // unsigned int get_closest_point(const gr_complex *sample);
      // void calc_arity();
      // virtual void constellation_bpsk();
      // void map_to_points(unsigned int value, gr_complex *points);
      // unsigned int decision_maker(const gr_complex *sample);

      /*
       * \param fft_len FFT length
       * \param constellation The constellation object describing the modulation used
       *                      on the subcarriers (e.g. QPSK). This is used to decode
       *                      the individual symbols.
       * \param occupied_carriers List of occupied carriers, see ofdm_carrier_allocator
       *                          for a description.
       * \param pilot_carriers Position of pilot symbols, see ofdm_carrier_allocator
       *                          for a description.
       * \param pilot_symbols Value of pilot symbols, see ofdm_carrier_allocator
       *                          for a description.
       * \param alpha Averaging coefficient (in a nutshell, if \f$H_{i,k}\f$ is the channel
       *              state for carrier i and symbol k,
       *              \f$H_{i,k+1} =  \alpha H_{i,k} + (1 - \alpha) H_{i,k+1}\f$. Make this
       *              larger if there's more noise, but keep in mind that larger values
       *              of alpha mean slower response to channel changes).
       * \param symbols_skipped Starting position within occupied_carriers and pilot_carriers.
       *                        If the first symbol of the frame was removed (e.g. to decode the
       *                        header), set this make sure the pilot symbols are correctly
       *                        identified.
       * \param input_is_shifted Set this to false if the input signal is not shifted, i.e.
       *                         the first input items is on the DC carrier.
       *                         Note that a lot of the OFDM receiver blocks operate on shifted
       *                         signals!
       */
      static sptr make(
	  int fft_len,
	  const gr::ofdm_allocator::constellation_alix_sptr &constellation,
	  const std::vector<std::vector<int> > &occupied_carriers = std::vector<std::vector<int> >(),
	  const std::vector<std::vector<int> > &pilot_carriers = std::vector<std::vector<int> >(),
	  const std::vector<std::vector<gr_complex> > &pilot_symbols = std::vector<std::vector<gr_complex> >(),
	  int symbols_skipped=0,
	  float alpha=0.1,
	  bool input_is_shifted=true
      );

     private:
      gr::ofdm_allocator::constellation_alix_sptr d_constellation;
      //! Averaging coefficient
      float d_alpha;
      // std::vector<gr_complex> d_constellation;
      // unsigned int d_rotational_symmetry;
      // unsigned int d_dimensionality;
      // unsigned int d_arity;
    };


  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_OFDM_EQUALIZER_SIMPLEDFE_ALIX_H */
