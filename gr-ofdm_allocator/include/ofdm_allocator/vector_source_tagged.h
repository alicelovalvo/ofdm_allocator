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


#ifndef INCLUDED_OFDM_ALLOCATOR_VECTOR_SOURCE_TAGGED_H
#define INCLUDED_OFDM_ALLOCATOR_VECTOR_SOURCE_TAGGED_H

#include <ofdm_allocator/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ofdm_allocator {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm_allocator
     *
     */
    class OFDM_ALLOCATOR_API vector_source_tagged : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<vector_source_tagged> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm_allocator::vector_source_tagged.
       *
       * To avoid accidental use of raw pointers, ofdm_allocator::vector_source_tagged's
       * constructor is in a private implementation
       * class. ofdm_allocator::vector_source_tagged::make is the public interface for
       * creating new instances.
       */
       static sptr make(const std::vector<int> &data,
                       bool repeat=false, int vlen=1, bool fixed=false,
                       const std::string &length_tag_key="vector_len",
                       const std::vector<tag_t> &tags=std::vector<tag_t>());

      virtual void rewind() = 0;
      virtual void set_data(const std::vector<int> &data,
                            const std::vector<tag_t> &tags=std::vector<tag_t>()) = 0;

      virtual void set_random_vector() = 0;
      virtual void set_repeat(bool repeat) = 0;    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_VECTOR_SOURCE_TAGGED_H */
