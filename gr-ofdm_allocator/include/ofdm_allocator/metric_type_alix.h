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


#ifndef INCLUDED_OFDM_ALLOCATOR_METRIC_TYPE_ALIX_H
#define INCLUDED_OFDM_ALLOCATOR_METRIC_TYPE_ALIX_H

// #include <ofdm_allocator/api.h>

namespace gr {
  namespace ofdm_allocator {

    typedef enum {
      TRELLIS_EUCLIDEAN = 200, TRELLIS_HARD_SYMBOL, TRELLIS_HARD_BIT
    } trellis_metric_type_t;

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_METRIC_TYPE_ALIX_H */
