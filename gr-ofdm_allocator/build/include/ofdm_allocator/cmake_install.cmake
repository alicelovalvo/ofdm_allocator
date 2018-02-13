# Install script for directory: /home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/lab/prefix/default")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ofdm_allocator" TYPE FILE FILES
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/api.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/vector_source_tagged.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/allocator_subcarrier.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/serializer_subcarrier.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/packet_header_default_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/packet_header_gen.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/packet_header_ofdm_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/ofdm_equalizer_base_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/ofdm_equalizer_simpledfe_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/frame_equalizer_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/constellation_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/metric_type_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/constellation_decoder_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/packet_header_parser_alix.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/per_measure.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/pkt_err_measure.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/per_measure_decimator.h"
    "/home/lab/prefix/default/src/gnuradio/gr-ofdm_allocator/include/ofdm_allocator/crc_alix.h"
    )
endif()

