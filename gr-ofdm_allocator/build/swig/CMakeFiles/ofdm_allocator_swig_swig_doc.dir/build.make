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

# Utility rule file for ofdm_allocator_swig_swig_doc.

# Include the progress variables for this target.
include swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/progress.make

swig/CMakeFiles/ofdm_allocator_swig_swig_doc: swig/ofdm_allocator_swig_doc.i


swig/ofdm_allocator_swig_doc.i: swig/ofdm_allocator_swig_doc_swig_docs/xml/index.xml
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/lab/ofdm_allocator/gr-ofdm_allocator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating python docstrings for ofdm_allocator_swig_doc"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/docs/doxygen && /usr/bin/python2 -B /home/lab/ofdm_allocator/gr-ofdm_allocator/docs/doxygen/swig_doc.py /home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig/ofdm_allocator_swig_doc_swig_docs/xml /home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig/ofdm_allocator_swig_doc.i

swig/ofdm_allocator_swig_doc_swig_docs/xml/index.xml: swig/_ofdm_allocator_swig_doc_tag
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/lab/ofdm_allocator/gr-ofdm_allocator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating doxygen xml for ofdm_allocator_swig_doc docs"
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig && ./_ofdm_allocator_swig_doc_tag
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig && /usr/bin/doxygen /home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig/ofdm_allocator_swig_doc_swig_docs/Doxyfile

ofdm_allocator_swig_swig_doc: swig/CMakeFiles/ofdm_allocator_swig_swig_doc
ofdm_allocator_swig_swig_doc: swig/ofdm_allocator_swig_doc.i
ofdm_allocator_swig_swig_doc: swig/ofdm_allocator_swig_doc_swig_docs/xml/index.xml
ofdm_allocator_swig_swig_doc: swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/build.make

.PHONY : ofdm_allocator_swig_swig_doc

# Rule to build all files generated by this target.
swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/build: ofdm_allocator_swig_swig_doc

.PHONY : swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/build

swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/clean:
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig && $(CMAKE_COMMAND) -P CMakeFiles/ofdm_allocator_swig_swig_doc.dir/cmake_clean.cmake
.PHONY : swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/clean

swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/depend:
	cd /home/lab/ofdm_allocator/gr-ofdm_allocator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lab/ofdm_allocator/gr-ofdm_allocator /home/lab/ofdm_allocator/gr-ofdm_allocator/swig /home/lab/ofdm_allocator/gr-ofdm_allocator/build /home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig /home/lab/ofdm_allocator/gr-ofdm_allocator/build/swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : swig/CMakeFiles/ofdm_allocator_swig_swig_doc.dir/depend

