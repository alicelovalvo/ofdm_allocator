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


#ifndef INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_H
#define INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_H

#include <ofdm_allocator/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API per_measure : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<per_measure> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::per_measure.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::per_measure's
       * constructor is in a private implementation
       * class. ofdm_allocator::per_measure::make is the public interface for
       * creating new instances.
       */
       static sptr make(size_t sizeof_stream_item,
                        int window);

       /*!
        * \brief Returns a vector of tag_t items as of the last call to
        * work.
        */
       virtual std::vector<tag_t> current_tags() = 0;

       /*!
        * \brief Return the total number of tags in the tag queue.
        */
       virtual int num_tags() = 0;


       /*!
        * \brief Set the display of tags to stdout on/off.
        */
       // virtual void set_display(bool d) = 0;

       /*!
        * \brief Set a new key to filter with.
        */
       // virtual void set_key_filter(const std::string &key_filter) = 0;

       /*!
        * \brief Get the current filter key.
        */
       // virtual std::string key_filter() const = 0;
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_H */
