# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lab/ofdm_allocator/gr-ofdm_allocator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lab/ofdm_allocator/gr-ofdm_allocator/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/test-ofdm_allocator.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/test-ofdm_allocator.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/test-ofdm_allocator.dir/flags.make

lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o: lib/CMakeFiles/test-ofdm_allocator.dir/flags.make
lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o: ../lib/test_ofdm_allocator.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lab/ofdm_allocator/gr-ofdm_allocator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o -c /home/lab/ofdm_allocator/gr-ofdm_allocator/lib/test_ofdm_allocator.cc

lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.i"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lab/ofdm_allocator/gr-ofdm_allocator/lib/test_ofdm_allocator.cc > CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.i

lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.s"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lab/ofdm_allocator/gr-ofdm_allocator/lib/test_ofdm_allocator.cc -o CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.s

lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o.requires:

.PHONY : lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o.requires

lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o.provides: lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-ofdm_allocator.dir/build.make lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o.provides

lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o.provides.build: lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o


lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o: lib/CMakeFiles/test-ofdm_allocator.dir/flags.make
lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o: ../lib/qa_ofdm_allocator.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lab/ofdm_allocator/gr-ofdm_allocator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o -c /home/lab/ofdm_allocator/gr-ofdm_allocator/lib/qa_ofdm_allocator.cc

lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.i"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lab/ofdm_allocator/gr-ofdm_allocator/lib/qa_ofdm_allocator.cc > CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.i

lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.s"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lab/ofdm_allocator/gr-ofdm_allocator/lib/qa_ofdm_allocator.cc -o CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.s

lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o.requires:

.PHONY : lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o.requires

lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o.provides: lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o.requires
	$(MAKE) -f lib/CMakeFiles/test-ofdm_allocator.dir/build.make lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o.provides.build
.PHONY : lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o.provides

lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o.provides.build: lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o


# Object files for target test-ofdm_allocator
test__ofdm_allocator_OBJECTS = \
"CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o" \
"CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o"

# External object files for target test-ofdm_allocator
test__ofdm_allocator_EXTERNAL_OBJECTS =

lib/test-ofdm_allocator: lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o
lib/test-ofdm_allocator: lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o
lib/test-ofdm_allocator: lib/CMakeFiles/test-ofdm_allocator.dir/build.make
lib/test-ofdm_allocator: /home/lab/prefix/stable/lib/libgnuradio-runtime.so
lib/test-ofdm_allocator: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
lib/test-ofdm_allocator: /usr/lib/x86_64-linux-gnu/libboost_system.so
lib/test-ofdm_allocator: /usr/lib/x86_64-linux-gnu/libcppunit.so
lib/test-ofdm_allocator: lib/libgnuradio-ofdm_allocator.so
lib/test-ofdm_allocator: /home/lab/prefix/stable/lib/libgnuradio-runtime.so
lib/test-ofdm_allocator: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
lib/test-ofdm_allocator: /usr/lib/x86_64-linux-gnu/libboost_system.so
lib/test-ofdm_allocator: lib/CMakeFiles/test-ofdm_allocator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lab/ofdm_allocator/gr-ofdm_allocator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test-ofdm_allocator"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-ofdm_allocator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/test-ofdm_allocator.dir/build: lib/test-ofdm_allocator

.PHONY : lib/CMakeFiles/test-ofdm_allocator.dir/build

lib/CMakeFiles/test-ofdm_allocator.dir/requires: lib/CMakeFiles/test-ofdm_allocator.dir/test_ofdm_allocator.cc.o.requires
lib/CMakeFiles/test-ofdm_allocator.dir/requires: lib/CMakeFiles/test-ofdm_allocator.dir/qa_ofdm_allocator.cc.o.requires

.PHONY : lib/CMakeFiles/test-ofdm_allocator.dir/requires

lib/CMakeFiles/test-ofdm_allocator.dir/clean:
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/test-ofdm_allocator.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/test-ofdm_allocator.dir/clean

lib/CMakeFiles/test-ofdm_allocator.dir/depend:
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lab/ofdm_allocator/gr-ofdm_allocator /home/lab/ofdm_allocator/gr-ofdm_allocator/lib /home/lab/ofdm_allocator/gr-ofdm_allocator/build /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib /home/lab/ofdm_allocator/gr-ofdm_allocator/build/lib/CMakeFiles/test-ofdm_allocator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/test-ofdm_allocator.dir/depend

