# Install script for directory: /home/alice/rfnoc/src/gr-ofdm_allocator/grc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_vector_source_tagged.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_allocator_subcarrier.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_ofdm_tx.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_serializer_subcarrier.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_packet_header_default_alix.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_packet_header_gen.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_packet_header_ofdm_alix.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_ofdm_equalizer_base_alix.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_ofdm_equalizer_simpledfe_alix.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_frame_equalizer_alix.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_constellation_alix.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_metric_type_alix.xml"
    "/home/alice/rfnoc/src/gr-ofdm_allocator/grc/ofdm_allocator_constellation_decoder_alix.xml"
    )
endif()

