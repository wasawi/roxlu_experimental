# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = "/Applications/CMake 2.8-3.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-3.app/Contents/bin/cmake" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-3.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/build

# Include any dependencies generated for this target.
include CMakeFiles/empty.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/empty.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/empty.dir/flags.make

CMakeFiles/empty.dir/src/main.cpp.o: CMakeFiles/empty.dir/flags.make
CMakeFiles/empty.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/empty.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/empty.dir/src/main.cpp.o -c /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/src/main.cpp

CMakeFiles/empty.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/empty.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/src/main.cpp > CMakeFiles/empty.dir/src/main.cpp.i

CMakeFiles/empty.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/empty.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/src/main.cpp -o CMakeFiles/empty.dir/src/main.cpp.s

CMakeFiles/empty.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/empty.dir/src/main.cpp.o.requires

CMakeFiles/empty.dir/src/main.cpp.o.provides: CMakeFiles/empty.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/empty.dir/build.make CMakeFiles/empty.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/empty.dir/src/main.cpp.o.provides

CMakeFiles/empty.dir/src/main.cpp.o.provides.build: CMakeFiles/empty.dir/src/main.cpp.o
.PHONY : CMakeFiles/empty.dir/src/main.cpp.o.provides.build

# Object files for target empty
empty_OBJECTS = \
"CMakeFiles/empty.dir/src/main.cpp.o"

# External object files for target empty
empty_EXTERNAL_OBJECTS =

empty: CMakeFiles/empty.dir/src/main.cpp.o
empty: ../../libglfw.a
empty: CMakeFiles/empty.dir/build.make
empty: CMakeFiles/empty.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable empty"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/empty.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/empty.dir/build: empty
.PHONY : CMakeFiles/empty.dir/build

CMakeFiles/empty.dir/requires: CMakeFiles/empty.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/empty.dir/requires

CMakeFiles/empty.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/empty.dir/cmake_clean.cmake
.PHONY : CMakeFiles/empty.dir/clean

CMakeFiles/empty.dir/depend:
	cd /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/build /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/build /Users/diederickhuijbers/of/addons_diederick/roxlu/tests/glfw/empty/build/CMakeFiles/empty.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/empty.dir/depend

