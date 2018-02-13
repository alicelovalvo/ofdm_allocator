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

#ifndef INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_IMPL_H
#define INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_IMPL_H

#include <ofdm_allocator/per_measure.h>

namespace gr {
  namespace ofdm_allocator {

    class per_measure_impl : public per_measure
    {
     private:
       std::string d_name;
       std::vector<tag_t> d_tags;
       std::vector<tag_t>::iterator d_tags_itr;
       bool d_display;
       int d_packet_init;
       int d_packet_number;
       int d_num_pkt_rcv;
       int d_window;
       pmt::pmt_t d_filter;
       gr::thread::mutex d_mutex;

     public:
      per_measure_impl(size_t sizeof_stream_item, int window);
      ~per_measure_impl();

      void setup_rpc();

      std::vector<tag_t> current_tags();
      int num_tags();


      // void set_display(bool d);

      // void set_key_filter(const std::string &key_filter);
      // std::string key_filter() const;


      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ofdm_allocator
} // namespace gr

#endif /* INCLUDED_OFDM_ALLOCATOR_PER_MEASURE_IMPL_H */