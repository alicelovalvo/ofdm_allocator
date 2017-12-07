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
#include "vector_source_tagged_impl.h"

namespace gr {
  namespace ofdm_allocator {

    vector_source_tagged::sptr
    vector_source_tagged::make(const std::vector<int> &data,
                 bool repeat, int vlen, bool fixed,
                 const std::string &length_tag_key,
                 const std::vector<tag_t> &tags)
    {
      return gnuradio::get_initial_sptr
        (new vector_source_tagged_impl(data, repeat, vlen, fixed, length_tag_key, tags));
    }

    /*
     * The private constructor
     */
    vector_source_tagged_impl::vector_source_tagged_impl(
      const std::vector<int> &data,
      bool repeat, int vlen, bool fixed,
      const std::string &length_tag_key,
      const std::vector<tag_t> &tags
    )
      : gr::sync_block("vector_source_tagged",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(int)*vlen)),
      d_data(data),
      d_repeat(repeat),
      d_fixed(fixed),
      d_offset(0),
      d_vlen(vlen),
      d_i(0),
      d_size(0),
      d_len_tag_key(pmt::string_to_symbol(length_tag_key)),
      d_tags(tags),
      d_tagpos(0)
    {
      if(tags.size() == 0) {
      d_settags = 0;
      }else {
        d_settags = 1;
        // for(int i=0; i < data.size(); i++){
        //set_output_multiple(48);
        // }
      }
      set_output_multiple(480);
      // if((d_data.size() % vlen) != 0)
      //   throw std::invalid_argument("data length must be a multiple of vlen");
    }

    /*
     * Our virtual destructor.
     */
    vector_source_tagged_impl::~vector_source_tagged_impl()
    {
    }

    void
    vector_source_tagged_impl::set_data (const std::vector<int> &data,
                           const std::vector<tag_t> &tags)
    {
      d_data = data;
      d_tags = tags;
      rewind();
      if(tags.size() == 0) {
        d_settags = false;
      }
      else {
        d_settags = true;
      }
    }

    void
    vector_source_tagged_impl::set_random_vector()
    {
      // std::cout << "####################################################" << '\n';
      timeval tv;
      gettimeofday(&tv, 0);
      // int time_ui = int(time(NULL));
      srand(tv.tv_usec);
      int length_vector = (rand() % 10) + 1;
      // std::cout << "/* length_vector */" << length_vector << '\n';
      int seed = rand();
      srand(seed);
      std::vector<int> sub_vec_vec(480);
      for (int f=0; f<length_vector; f++){
        std::vector<int> sub_vec(48);
        int length = (rand() % 43) + 6;
        int i = 0;
        for(i=0; i<length; ){
          int temp_2 = 0;
          int temp = rand() % 53 - 26;
              if (i == 0 && !(abs(temp) == 21 || abs(temp) == 7 || temp == 0)){
                  std::fill (sub_vec.begin(),sub_vec.begin()+i+1,temp);
                  i = i + 1;
                }
              else{
                  for(int j = 0; j<i; j++){
                      // # print"-------"
                      // # print"z[",j,"]=",z[j]," and temp",temp
                      if (sub_vec[j] == temp || abs(temp) == 21 || abs(temp) == 7 || temp == 0){
                          temp_2 = 1;
                      //     # print"temp_2"
                      // # print"-------"
                      }
                  }
                  if (i != 0){
                      if (temp_2 == 0){
                          std::fill (sub_vec.begin()+i,sub_vec.begin()+i+1,temp);
                          i = i + 1;
                        }
                      else{
                          continue;
                        }
                      }
                    }
              }
          std::sort(sub_vec.begin(), sub_vec.end());

          for(int l=0; l < 48; l++){
          std::fill (sub_vec_vec.begin()+((f*48)+l),sub_vec_vec.begin()+((f*48)+1+l),sub_vec[l]);
        }
      }

      // std::cout << "/* sub_vec_vec */ ";
      //   for (int i = 0; i < sub_vec_vec.size(); i++){
      //     // for (int j=0; j<sub_vec_vec[i].size(); j++){
      //       std::cout << sub_vec_vec[i] << ", ";
      //     }
      //     std::cout << '\n';
        // }
        d_data = sub_vec_vec;


        //return sub_vec;

    }


    int
    vector_source_tagged_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {


      int *optr = (int *) output_items[0];

      // set_relative_rate((double) 2.0);

      if(d_repeat) {
        unsigned int size = d_data.size ();
        unsigned int offset = d_offset;
        unsigned n = std::min((unsigned)d_data.size(),
                              (unsigned)noutput_items*d_vlen);

        if(size == 0)
          return -1;
          d_i++;
          // std::cout << "###################################################################### d_i: " << d_i << '\n';

        if(d_settags) {
          int n_outputitems_per_vector = d_data.size() / d_vlen;
          for(int i = 0; i < noutput_items; i += n_outputitems_per_vector) {
            // FIXME do proper vector copy
            memcpy((void *) optr, (const void*)&d_data[0], size*sizeof (int));
            optr += size;
            for(unsigned t = 0; t < d_tags.size(); t++) {
              add_item_tag(0, nitems_written(0)+i+d_tags[t].offset,
                           d_tags[t].key, d_tags[t].value, d_tags[t].srcid);
            }
          }
        }
        else {


          // for(int i = 0; i < noutput_items; i ++) {
          //   // FIXME do proper vector copy
          //   memcpy((void *) optr, (const void*)&d_data[0], size*sizeof (int));
          //   optr[i] = d_data[i];
          //
          // }
          // memcpy((void *) optr, (const void*)&d_data[0], size*sizeof (int));
          // optr += size;
        //   int n_outputitems_per_vector = d_data.size() / d_vlen;
        //     for(int j = 0; j < noutput_items; j += n_outputitems_per_vector) {
        //       for(unsigned i = 0; i < n; i++) {
        //         optr[i+j] = d_data[i];
        //         add_item_tag(0, nitems_written(0) + d_size, d_len_tag_key, d_vector_len_pmt);
        //         d_size += size;
        //   }
        // }
        if(!d_fixed){
         vector_source_tagged_impl::set_random_vector();
       }
         unsigned int size = d_data.size ();
         pmt::pmt_t d_vector_len_pmt = pmt::from_long(size);
// std::cout << "/* length */" << d_data.size() <<'\n';
//         for(int i=0; i<d_data.size(); i++){
//           for (int j=0; j < d_data[i].size(); j++){
//             std::cout << d_data[i][j] << ", ";
//           }
//         }
//         std::cout << '\n';
          // std::cout << "/* size */" << size << '\n';
          // std::cout << "/* optr */ ";
          for(int i = 0; i < noutput_items*d_vlen; i++) {
            // d_vector_len_pmt = pmt::from_long(d_data[i].size());
           // for(int j = 0; j < d_data.size(); j++) {
            optr[i] = d_data[offset++];
            // std::cout << optr[i] << ", ";
            if(offset >= size) {
              offset = 0;
              // std::cout << '\n';
              // std::cout << "/* optr */ ";
              if(!d_fixed){
                vector_source_tagged_impl::set_random_vector();
              }
            }
          add_item_tag(0, nitems_written(0) + i, d_len_tag_key, d_vector_len_pmt);

        }
            // d_size += size;



          // std::cout << "/* size */" << size << '\n';
          // std::cout << "/* offset */" << offset << '\n';
          // std::cout << "/* nitems_written */" << nitems_written(0) << '\n';
          //std::cout << "/* noutput_items */" << noutput_items << '\n';

           // while(d_tagpos < nitems_written(0) + size) {
           // d_tagpos += size;
          // }
        }

        // d_offset = offset;
        // d_size +=size;
        d_offset = 0;
        return noutput_items;
      }
      else {
        if(d_offset >= d_data.size ())
          return -1;  // Done!

        unsigned n = std::min((unsigned)d_data.size() - d_offset,
                              (unsigned)noutput_items*d_vlen);
        for(unsigned i = 0; i < n; i++) {
          optr[i] = d_data[d_offset + i];
        }
        for(unsigned t = 0; t < d_tags.size(); t++) {
          if((d_tags[t].offset >= d_offset) && (d_tags[t].offset < d_offset+n))
            add_item_tag(0, d_tags[t].offset, d_tags[t].key, d_tags[t].value,
                         d_tags[t].srcid);
        }
        d_offset += n;
        return n/d_vlen;
      }
    }


  } /* namespace ofdm_allocator */
} /* namespace gr */
