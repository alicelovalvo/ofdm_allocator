# Install script for directory: /Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/opt/local")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ofdm_allocator" TYPE FILE FILES
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/api.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/vector_source_tagged.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/allocator_subcarrier.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/serializer_subcarrier.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/packet_header_default_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/packet_header_gen.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/packet_header_ofdm_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/ofdm_equalizer_base_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/ofdm_equalizer_simpledfe_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/frame_equalizer_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/constellation_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/metric_type_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/constellation_decoder_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/packet_header_parser_alix.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/per_measure.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/pkt_err_measure.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/per_measure_decimator.h"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/include/ofdm_allocator/crc_alix.h"
    )
endif()

