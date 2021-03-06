# Install script for directory: /home/lab/ofdm_allocator/gr-ofdm_allocator

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/lab/prefix/stable")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ofdm_allocator" TYPE FILE FILES "/home/lab/ofdm_allocator/gr-ofdm_allocator/cmake/Modules/ofdm_allocatorConfig.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/lab/ofdm_allocator/gr-ofdm_allocator/build/include/ofdm_allocator/cmake_install.cmake")
  include("/home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib/cmake_install.cmake")
  include("/home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig/cmake_install.cmake")
  include("/home/lab/ofdm_allocator/gr-ofdm_allocator/build/python/cmake_install.cmake")
  include("/home/lab/ofdm_allocator/gr-ofdm_allocator/build/grc/cmake_install.cmake")
  include("/home/lab/ofdm_allocator/gr-ofdm_allocator/build/apps/cmake_install.cmake")
  include("/home/lab/ofdm_allocator/gr-ofdm_allocator/build/docs/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/lab/ofdm_allocator/gr-ofdm_allocator/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
