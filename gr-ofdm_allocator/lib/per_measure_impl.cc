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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "per_measure_impl.h"

namespace gr {
  namespace ofdm_allocator {

    per_measure::sptr
    per_measure::make(size_t sizeof_stream_item,
                    const int window)
    {
      return gnuradio::get_initial_sptr
        (new per_measure_impl(sizeof_stream_item, window));
    }

    /*
     * The private constructor
     */
    per_measure_impl::per_measure_impl(size_t sizeof_stream_item,
                                   int window)
      : gr::sync_block("per_measure",
              gr::io_signature::make(1, -1, sizeof_stream_item),
              gr::io_signature::make(1, 1, sizeof(float))),
              // gr::io_signature::make(0, 0, 0)),
        d_packet_init(0), d_num_pkt_rcv(0), d_window(window), d_packet_number(0)
    {
    }

    /*
     * Our virtual destructor.
     */
    per_measure_impl::~per_measure_impl()
    {
    }

    std::vector<tag_t>
    per_measure_impl::current_tags()
    {
      gr::thread::scoped_lock l(d_mutex);
      return d_tags;
    }

    int
    per_measure_impl::num_tags()
    {
      std::vector<tag_t> t;
      get_tags_in_range(t, 0, 0, nitems_read(0));
      return static_cast<int>(t.size());
    }

    // void
    // per_measure_impl::set_display(bool d)
    // {
    //   d_display = d;
    // }

    int
    per_measure_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      gr::thread::scoped_lock l(d_mutex);
      float *out = (float*)output_items[0];
      bool toprint = false;
      int packet_number = 0;
      double packet_error_rate = 0;
      int sub = 0;

      // std::stringstream sout;
      // if(d_display) {
      //   sout << std::endl
      //        << "----------------------------------------------------------------------";
      //   sout << std::endl << "Tag Debug: " << d_name << std::endl;
      // }


      uint64_t abs_N, end_N;
      for(size_t i = 0; i < input_items.size(); i++) {
        abs_N = nitems_read(i);
        end_N = abs_N + (uint64_t)(noutput_items);

        d_tags.clear();

        // if(pmt::is_null(d_filter))
          get_tags_in_range(d_tags, i, abs_N, end_N);
        // else{
        //   get_tags_in_range(d_tags, i, abs_N, end_N, d_filter);
        // }

        for (unsigned l = 0; l < d_tags.size(); l++) {
          if (pmt::symbol_to_string(d_tags[l].key) == "packet_num") {
            packet_number = pmt::to_long(d_tags[l].value) + 1;

            d_packet_number = pmt::to_long(d_tags[l].value) + 1;
            // if (packet_number == 0){
            //   d_packet_init = 0;
            //   d_num_pkt_rcv = 0;
            // }
            d_num_pkt_rcv++;
            // std::cout << "/* message_pkt */" << d_packet_number << '\n';
          }
        }

        if(d_packet_number < d_packet_init){
          // std::cout << "/* d_packet_init */" << d_packet_init << '\n';
          d_packet_init = - (4096 - d_packet_init);
          // std::cout << "/* packet_number */" << d_packet_number << '\n';
          // std::cout << "/* d_packet_init_new */" << d_packet_init << '\n';
          sub = d_packet_number - d_packet_init;
          // std::cout << "/* sub */" << sub << '\n';
          // std::cout << "/*********************************************/" << '\n';
        } else{
          sub = (d_packet_number - d_packet_init);
        }

        if (sub >= d_window){
          // std::cout << "/* d_packet_init */" << d_packet_init << '\n';
          // std::cout << "/* packet_number */" << d_packet_number << '\n';
          d_packet_init = d_packet_number;
          packet_error_rate = (double)(10000 - (double)((d_num_pkt_rcv*10000)/sub))/100;
          std::cout << "PER " << packet_error_rate << '\n';
          // std::cout << "/* sub */" << sub << '\n';
          // std::cout << "/* num_pkt_rcv */" << d_num_pkt_rcv << '\n';
          // std::cout << "/*********************************************/" << '\n';
          d_num_pkt_rcv = 0;

          // std::cout << "/* noutput_items_1 */" << noutput_items << '\n';
          for(int m = 0; m < noutput_items; m++) {
            out[m] = (float)packet_error_rate;
            // return noutput_items;
            // std::cout << "/* out */" << out[m]  <<'\n';
          }

        }

        // if(d_tags.size() > 0) {
        //   toprint = true;
        // }
        //
        // if(d_display) {
        //   sout << "Input Stream: " << std::setw(2) << std::setfill('0')
        //        << i << std::setfill(' ') << std::endl;
        //   for(d_tags_itr = d_tags.begin(); d_tags_itr != d_tags.end(); d_tags_itr++) {
        //     sout << std::setw(10) << "Offset: " << d_tags_itr->offset
        //          << std::setw(10) << "Source: "
        //          << (pmt::is_symbol(d_tags_itr->srcid) ? pmt::symbol_to_string(d_tags_itr->srcid) : "n/a")
        //          << std::setw(10) << "Key: " << pmt::symbol_to_string(d_tags_itr->key)
        //          << std::setw(10) << "Value: ";
        //     sout << d_tags_itr->value << std::endl;
        //   }
        // }
      }

      // if(d_display) {
      //   sout << "----------------------------------------------------------------------";
      //   sout << std::endl;
      //
      //   if(toprint) {
      //     std::cout << sout.str();
      //   }
      // }
      return noutput_items;
      // return 0;
    }

    void
    per_measure_impl::setup_rpc()
    {
#ifdef GR_CTRLPORT
      add_rpc_variable(
        rpcbasic_sptr(new rpcbasic_register_get<tag_debug, int>(
    alias(), "num. tags",
    &tag_debug::num_tags,
    pmt::from_long(0), pmt::from_long(10000), pmt::from_long(0),
    "", "Number of Tags", RPC_PRIVLVL_MIN,
          DISPTIME | DISPOPTSTRIP)));
#endif /* GR_CTRLPORT */
    }

  } /* namespace ofdm_allocator */
} /* namespace gr */
