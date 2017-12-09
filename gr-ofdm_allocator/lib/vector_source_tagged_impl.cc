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
                 bool repeat, int vlen, bool fixed_data, int fft_len,
                 int max_len_data_subcarr, int max_len_pilot_subcarr,
                 int max_vector_data_subcarr, int max_vector_pilot_subcarr,
                 bool fixed_pilot, const std::vector<int> &pilot,
                 const std::string &length_tag_key,
                 const std::vector<tag_t> &tags)
    {
      return gnuradio::get_initial_sptr
        (new vector_source_tagged_impl(data, repeat, vlen, fixed_data, fft_len, max_len_data_subcarr, max_len_pilot_subcarr, max_vector_data_subcarr, max_vector_pilot_subcarr, fixed_pilot, pilot, length_tag_key, tags));
    }

    /*
     * The private constructor
     */
    vector_source_tagged_impl::vector_source_tagged_impl(
      const std::vector<int> &data,
      bool repeat, int vlen, bool fixed_data, int fft_len,
      int max_len_data_subcarr, int max_len_pilot_subcarr,
      int max_vector_data_subcarr, int max_vector_pilot_subcarr,
      bool fixed_pilot, const std::vector<int> &pilot,
      const std::string &length_tag_key,
      const std::vector<tag_t> &tags
    )
      : gr::sync_block("vector_source_tagged",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(int)*vlen)),
      d_data(data),
      d_pilot(pilot),
      d_repeat(repeat),
      d_fixed_data(fixed_data),
      d_fixed_pilot(fixed_pilot),
      d_offset(0),
      d_vlen(vlen),
      d_fft_len(fft_len),
      d_data_sub(max_len_data_subcarr),
      d_pilot_sub(max_len_pilot_subcarr),
      d_vector_data(max_vector_data_subcarr),
      d_vector_pilot(max_vector_pilot_subcarr),
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
        // }
      }
      set_output_multiple((d_data_sub*d_vector_data)+(d_pilot_sub*d_vector_pilot));
      // std::cout << "/* message */" << d_data_sub << '\n';
      // std::cout << "/* message */" << d_vector_data << '\n';
      // std::cout << "/* message */" << d_pilot_sub << '\n';
      // std::cout << "/* message */" << d_vector_pilot << '\n';

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
    vector_source_tagged_impl::final_update()
    {
      d_final_subcarrier.erase(d_final_subcarrier.begin(),d_final_subcarrier.end());
      for(int i=0; i<d_data.size(); i++){
        d_final_subcarrier.push_back(d_data[i]);
      }
      for(int j=0; j<d_pilot.size(); j++){
        d_final_subcarrier.push_back(d_pilot[j]);
      }
      // std::cout << "/* d_final_subcarrier */ " << '\n';
      // for(int j=0; j<d_final_subcarrier.size(); j++){
      //   std::cout << d_final_subcarrier[j];
      // }
      // std::cout << '\n';
      // set_output_multiple(d_final_subcarrier.size());

    }

    void
    vector_source_tagged_impl::set_random_vector_pilot()
    {
	std::vector<int> sub_vec_vec_pilot(d_vector_pilot*d_pilot_sub);
        timeval tv;
        gettimeofday(&tv, 0);
        // int time_ui = int(time(NULL));
        srand(tv.tv_usec);
        int length_vector = (rand() % d_vector_pilot) + 1;
        //std::cout << "/* length_vector */" << length_vector << '\n';
        int seed = rand();
        int interval = round((d_fft_len * 83) / 100);
        srand(seed);
        for (int f = 0; f < length_vector; f++){
          std::vector<int> sub_vec_pilot(d_pilot_sub);
          int i = 0;
          for(i=0; i<d_pilot_sub; ){
            int temp_2 = 0;
            int temp = (rand() % interval) - ((interval - 1)/2);
            //std::cout << "/* interval */" << interval << '\n';
            if (i == 0 && !(temp == 0)){
              std::fill (sub_vec_pilot.begin(),sub_vec_pilot.begin()+i+1,temp);
              i = i + 1;
            }
            else{
              for(int j = 0; j<i; j++){
                // # print"-------"
                // # print"z[",j,"]=",z[j]," and temp",temp
                if (d_pilot[j] == temp || temp == 0){
                  temp_2 = 1;
                  //     # print"temp_2"
                  // # print"-------"
                }
              }
              if (i != 0){
                if (temp_2 == 0){
                  std::fill (sub_vec_pilot.begin()+i,sub_vec_pilot.begin()+i+1,temp);
                  i = i + 1;
                }
                else{
                  continue;
                }
              }
             }
          }
          std::sort(sub_vec_pilot.begin(), sub_vec_pilot.end());

          for(int l=0; l < d_pilot_sub; l++){
              std::fill (sub_vec_vec_pilot.begin()+((f*d_pilot_sub)+l),sub_vec_vec_pilot.begin()+((f*d_pilot_sub)+1+l),sub_vec_pilot[l]);
          }

      }
	d_pilot = sub_vec_vec_pilot;
    }

    void
    vector_source_tagged_impl::set_random_vector_data()
    {
      // std::cout << "####################################################" << '\n';
      //std::vector<int> sub_vec_vec(1);
    std::vector<int> sub_vec_vec(d_vector_data*d_data_sub);
        timeval tv;
        gettimeofday(&tv, 0);
        // int time_ui = int(time(NULL));
        srand(tv.tv_usec);
        int length_vector = (rand() % d_vector_data) + 1;
        // std::cout << "/* length_vector */" << length_vector << '\n';
        int seed = rand();
        int interval = round((d_fft_len * 83) / 100);
        // std::cout << "/* interval */" << interval << '\n';
        srand(seed);
        for (int f = 0; f < length_vector; f++){
          std::vector<int> sub_vec(d_data_sub);
          int length = (rand() % (d_data_sub - 5)) + 6;
          int i = 0;
          for(i=0; i<length; ){
            int temp_2 = 0;
            int temp = (rand() % interval) - ((interval - 1)/2);
            if (i == 0 && !(abs(temp) == 21 || abs(temp) == 7 || temp == 0)){
              std::fill (sub_vec.begin(),sub_vec.begin()+i+1,temp);
              i = i + 1;
            }
            else{
              for(int j = 0; j<i; j++){
                // # print"-------"
                // # print"z[",j,"]=",z[j]," and temp",temp
                if (sub_vec[j] == temp || temp == 0){
                  temp_2 = 1;
                  //     # print"temp_2"
                  // # print"-------"
                }
              }
                for(int j = 0; j<4; j++){
                  if (d_pilot[(f*4)+j] == temp){
                    temp_2 = 1;
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

          for(int l=0; l < d_data_sub; l++){
            std::fill (sub_vec_vec.begin()+((f*d_data_sub)+l),sub_vec_vec.begin()+((f*d_data_sub)+1+l),sub_vec[l]);
          }
        }
        d_data = sub_vec_vec;
        //std::cout << "/* sub_vec_vec */ ";
        //for (int i = 0; i < sub_vec_vec.size(); i++){
        //  // for (int j=0; j<sub_vec_vec[i].size(); j++){
        //  std::cout << sub_vec_vec[i] << ", ";
        //}
        //std::cout << '\n';
      }

      // std::cout << "/* sub_vec_vec */" << sub_vec_vec.size() << '\n';
      // }
        //return sub_vec;




    int
    vector_source_tagged_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {


      int *optr = (int *) output_items[0];


      // set_relative_rate((double) 2.0);

      if(d_repeat) {
        unsigned int size = d_data.size ();
        unsigned int offset_final = d_offset;
	      unsigned int offset_data = 0;
        unsigned int offset_pilot = 0;
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
        if(!d_fixed_pilot){
          vector_source_tagged_impl::set_random_vector_pilot();
        }
        if(!d_fixed_data){
          vector_source_tagged_impl::set_random_vector_data();
        }
        vector_source_tagged_impl::final_update();

        unsigned int size = d_data.size();
        unsigned int size_pilot = d_pilot.size();
        pmt::pmt_t d_vector_len_pmt = pmt::from_long(size+size_pilot);
        // std::cout << "/* length */" << d_data.size() <<'\n';
        //         for(int i=0; i<d_data.size(); i++){
        //           for (int j=0; j < d_data[i].size(); j++){
        //             std::cout << d_data[i][j] << ", ";
        //           }
        //         }
        //	std::vector<int> final_sub;
        //	for (int i=0; i<size; i++){
        //	   final_sub.push_back(d_data[i]);
        //	}
        //        for (int i=0; i<size_pilot; i++){
        //           final_sub.push_back(d_pilot[i]);
        //        }
        //        std::cout << "final ";
        //	for (int i=0; i<final_sub.size(); i++){
        //           std::cout << final_sub[i] << ",";
        //       }
        //        std::cout << '\n';
        //         std::cout << '\n';
        // std::cout << "/* size */" << size << '\n';
        // std::cout << "/* size_pilot */" << size_pilot << '\n';
        // std::cout << "/* noutput_items */" << noutput_items << '\n';
        //
        // std::cout << "/* optr1 */ ";
        int i;
        for(i = 0; i < noutput_items*d_vlen; i++) {
          // d_vector_len_pmt = pmt::from_long(d_data[i].size());
          //for(int i = 0; i < d_data.size(); i++) {
          optr[i] = d_final_subcarrier[offset_final++];

          if(offset_final>size){
            offset_pilot++;
          }

          if(offset_final<size){
            offset_data++;
          }
          //pilot_sub[i] = d_pilot[offset_pilot++];

          // std::cout << optr[i] << ", ";
          if(offset_pilot >= size_pilot) {
            offset_pilot = 0;
            //std::cout << '\n';
            //std::cout << "/* optr */ ";
            if(!d_fixed_pilot){
              vector_source_tagged_impl::set_random_vector_pilot();
              vector_source_tagged_impl::final_update();
            }
          }
            if(offset_data >= size) {
              offset_data = 0;
              // std::cout << '\n';
              // std::cout << "/* optr */ ";

              if(!d_fixed_data){
                vector_source_tagged_impl::set_random_vector_data();
                vector_source_tagged_impl::final_update();
              }
            }

            if(offset_final>=(size_pilot+size)){
              offset_final = 0;
              // std::cout << '\n';
              // std::cout << "/* optr */ ";
            }
            add_item_tag(0, nitems_written(0) + i, d_len_tag_key, d_vector_len_pmt);
          }
          // std::cout << "/* i */ " << i << '\n';
            // d_size += size;
          // std::cout << "/* size */" << size << '\n';
          // std::cout << "/* offset */" << offset << '\n';
          // std::cout << "/* nitems_written */" << nitems_written(0) << '\n';

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
