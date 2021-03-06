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


#ifndef INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_DECIMATOR_H
#define INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_DECIMATOR_H

#include <ofdm_allocator/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API per_measure_decimator : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<per_measure_decimator> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::per_measure_decimator.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::per_measure_decimator's
       * constructor is in a private implementation
       * class. ofdm_allocator::per_measure_decimator::make is the public interface for
       * creating new instances.
       */
      static sptr make(size_t sizeof_stream_item,
                        int window);

       virtual std::vector<tag_t> current_tags() = 0;

       /*!
        * \brief Return the total number of tags in the tag queue.
        */
       virtual int num_tags() = 0;
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_DECIMATOR_H */
