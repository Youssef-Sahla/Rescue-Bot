# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /usr/src/mjpg-streamer/mjpg-streamer-experimental

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/src/mjpg-streamer/mjpg-streamer-experimental

# Include any dependencies generated for this target.
include CMakeFiles/mjpg_streamer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mjpg_streamer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mjpg_streamer.dir/flags.make

CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o: CMakeFiles/mjpg_streamer.dir/flags.make
CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o: mjpg_streamer.c
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/src/mjpg-streamer/mjpg-streamer-experimental/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o   -c /usr/src/mjpg-streamer/mjpg-streamer-experimental/mjpg_streamer.c

CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /usr/src/mjpg-streamer/mjpg-streamer-experimental/mjpg_streamer.c > CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.i

CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /usr/src/mjpg-streamer/mjpg-streamer-experimental/mjpg_streamer.c -o CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.s

CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o.requires:
.PHONY : CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o.requires

CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o.provides: CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o.requires
	$(MAKE) -f CMakeFiles/mjpg_streamer.dir/build.make CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o.provides.build
.PHONY : CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o.provides

CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o.provides.build: CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o

CMakeFiles/mjpg_streamer.dir/utils.c.o: CMakeFiles/mjpg_streamer.dir/flags.make
CMakeFiles/mjpg_streamer.dir/utils.c.o: utils.c
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/src/mjpg-streamer/mjpg-streamer-experimental/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mjpg_streamer.dir/utils.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mjpg_streamer.dir/utils.c.o   -c /usr/src/mjpg-streamer/mjpg-streamer-experimental/utils.c

CMakeFiles/mjpg_streamer.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mjpg_streamer.dir/utils.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /usr/src/mjpg-streamer/mjpg-streamer-experimental/utils.c > CMakeFiles/mjpg_streamer.dir/utils.c.i

CMakeFiles/mjpg_streamer.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mjpg_streamer.dir/utils.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /usr/src/mjpg-streamer/mjpg-streamer-experimental/utils.c -o CMakeFiles/mjpg_streamer.dir/utils.c.s

CMakeFiles/mjpg_streamer.dir/utils.c.o.requires:
.PHONY : CMakeFiles/mjpg_streamer.dir/utils.c.o.requires

CMakeFiles/mjpg_streamer.dir/utils.c.o.provides: CMakeFiles/mjpg_streamer.dir/utils.c.o.requires
	$(MAKE) -f CMakeFiles/mjpg_streamer.dir/build.make CMakeFiles/mjpg_streamer.dir/utils.c.o.provides.build
.PHONY : CMakeFiles/mjpg_streamer.dir/utils.c.o.provides

CMakeFiles/mjpg_streamer.dir/utils.c.o.provides.build: CMakeFiles/mjpg_streamer.dir/utils.c.o

# Object files for target mjpg_streamer
mjpg_streamer_OBJECTS = \
"CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o" \
"CMakeFiles/mjpg_streamer.dir/utils.c.o"

# External object files for target mjpg_streamer
mjpg_streamer_EXTERNAL_OBJECTS =

mjpg_streamer: CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o
mjpg_streamer: CMakeFiles/mjpg_streamer.dir/utils.c.o
mjpg_streamer: CMakeFiles/mjpg_streamer.dir/build.make
mjpg_streamer: CMakeFiles/mjpg_streamer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable mjpg_streamer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mjpg_streamer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mjpg_streamer.dir/build: mjpg_streamer
.PHONY : CMakeFiles/mjpg_streamer.dir/build

CMakeFiles/mjpg_streamer.dir/requires: CMakeFiles/mjpg_streamer.dir/mjpg_streamer.c.o.requires
CMakeFiles/mjpg_streamer.dir/requires: CMakeFiles/mjpg_streamer.dir/utils.c.o.requires
.PHONY : CMakeFiles/mjpg_streamer.dir/requires

CMakeFiles/mjpg_streamer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mjpg_streamer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mjpg_streamer.dir/clean

CMakeFiles/mjpg_streamer.dir/depend:
	cd /usr/src/mjpg-streamer/mjpg-streamer-experimental && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/src/mjpg-streamer/mjpg-streamer-experimental /usr/src/mjpg-streamer/mjpg-streamer-experimental /usr/src/mjpg-streamer/mjpg-streamer-experimental /usr/src/mjpg-streamer/mjpg-streamer-experimental /usr/src/mjpg-streamer/mjpg-streamer-experimental/CMakeFiles/mjpg_streamer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mjpg_streamer.dir/depend

