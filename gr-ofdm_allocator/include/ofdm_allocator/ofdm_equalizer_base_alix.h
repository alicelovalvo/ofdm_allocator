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


#ifndef INCLUDED_OFDM_ALLOCATOR_OFDM_EQUALIZER_BASE_ALIX_H
#define INCLUDED_OFDM_ALLOCATOR_OFDM_EQUALIZER_BASE_ALIX_H

#include <ofdm_allocator/api.h>
#include <gnuradio/tags.h>
#include <gnuradio/gr_complex.h>
#include <boost/enable_shared_from_this.hpp>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description+>
     *
     */
    class OFDM_ALLOCATOR_API ofdm_equalizer_base_alix
    : public boost::enable_shared_from_this<ofdm_equalizer_base_alix>

    {
    protected:
     int d_fft_len;

    public:
     typedef boost::shared_ptr<ofdm_equalizer_base_alix> sptr;

     ofdm_equalizer_base_alix(int fft_len);
     // virtual ~ofdm_equalizer_base_alix();
     ~ofdm_equalizer_base_alix();

     //! Reset the channel information state knowledge
     virtual void reset() = 0;
     //! Run the actual equalization
     virtual void equalize(
         gr_complex *frame,
         int n_sym,
         const std::vector<gr_complex> &initial_taps = std::vector<gr_complex>(),
  	 const std::vector<bool> &occupied_carriers = std::vector<bool> (),
         const std::vector<tag_t> &tags = std::vector<tag_t>()) = 0;
     //! Return the current channel state
     virtual void get_channel_state(std::vector<gr_complex> &taps) = 0;
     int fft_len() { return d_fft_len; };
     sptr base() { return shared_from_this(); };
   };


   /* \brief Base class for implementation details of 1-dimensional OFDM FDEs which use pilot tones.
    * \ingroup digital
    *
    */
   class OFDM_ALLOCATOR_API ofdm_equalizer_1d_pilots_alix : public ofdm_equalizer_base_alix
   {
    protected:
     //! If \p d_occupied_carriers[k][l] is true, symbol k, carrier l is carrying data.
     //  (this is a different format than occupied_carriers!)
     std::vector<bool> d_occupied_carriers;
     //! If \p d_pilot_carriers[k][l] is true, symbol k, carrier l is carrying data.
     //  (this is a different format than pilot_carriers!)
     std::vector<std::vector<bool> > d_pilot_carriers;
     //! If \p d_pilot_carriers[k][l] is true, d_pilot_symbols[k][l] is its tx'd value.
     //  (this is a different format than pilot_symbols!)
     std::vector<std::vector<gr_complex> > d_pilot_symbols;
     //! In case the frame doesn't begin with OFDM symbol 0, this is the index of the first symbol
     int d_symbols_skipped;
     //! The current position in the set of pilot symbols
     int d_pilot_carr_set;
     //! Vector of length d_fft_len saving the current channel state (on the occupied carriers)
     std::vector<gr_complex> d_channel_state;

    public:
     typedef boost::shared_ptr<ofdm_equalizer_1d_pilots_alix> sptr;

     ofdm_equalizer_1d_pilots_alix(
   int fft_len,
   const std::vector<std::vector<int> > &occupied_carriers,
   const std::vector<std::vector<int> > &pilot_carriers,
   const std::vector<std::vector<gr_complex> > &pilot_symbols,
   int symbols_skipped,
   bool input_is_shifted);
     ~ofdm_equalizer_1d_pilots_alix();

     void reset();
     void get_channel_state(std::vector<gr_complex> &taps);
   };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_OFDM_EQUALIZER_BASE_ALIX_H */
