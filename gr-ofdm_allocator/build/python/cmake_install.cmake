# Install script for directory: /Users/Alice/ofdm_allocator/gr-ofdm_allocator/python

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/site-packages/ofdm_allocator" TYPE FILE FILES
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/python/__init__.py"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/python/ofdm_tx.py"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/site-packages/ofdm_allocator" TYPE FILE FILES
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/build/python/__init__.pyc"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/build/python/ofdm_tx.pyc"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/build/python/__init__.pyo"
    "/Users/Alice/ofdm_allocator/gr-ofdm_allocator/build/python/ofdm_tx.pyo"
    )
endif()

