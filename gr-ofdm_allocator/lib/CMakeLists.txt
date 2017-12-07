# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND ofdm_allocator_sources
    vector_source_tagged_impl.cc
    allocator_subcarrier_impl.cc
    serializer_subcarrier_impl.cc
    packet_header_default_alix.cc
    packet_header_gen_impl.cc
    packet_header_ofdm_alix.cc
    ofdm_equalizer_base_alix.cc
    ofdm_equalizer_simpledfe_alix.cc
    frame_equalizer_alix_impl.cc
    constellation_alix.cc
    constellation_decoder_alix_impl.cc )

set(ofdm_allocator_sources "${ofdm_allocator_sources}" PARENT_SCOPE)
if(NOT ofdm_allocator_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT ofdm_allocator_sources)

add_library(gnuradio-ofdm_allocator SHARED ${ofdm_allocator_sources})
target_link_libraries(gnuradio-ofdm_allocator ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-ofdm_allocator PROPERTIES DEFINE_SYMBOL "gnuradio_ofdm_allocator_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-ofdm_allocator PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-ofdm_allocator
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_ofdm_allocator_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ofdm_allocator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_ofdm_allocator.cc
    )

add_executable(test-ofdm_allocator ${test_ofdm_allocator_sources})

target_link_libraries(
  test-ofdm_allocator
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-ofdm_allocator
)

GR_ADD_TEST(test_ofdm_allocator test-ofdm_allocator)
