# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/leo/code/IntroToOpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leo/code/IntroToOpenGL/build

# Include any dependencies generated for this target.
include CMakeFiles/ITOG.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ITOG.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ITOG.dir/flags.make

CMakeFiles/ITOG.dir/src/main.cpp.o: CMakeFiles/ITOG.dir/flags.make
CMakeFiles/ITOG.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leo/code/IntroToOpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ITOG.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ITOG.dir/src/main.cpp.o -c /home/leo/code/IntroToOpenGL/src/main.cpp

CMakeFiles/ITOG.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITOG.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leo/code/IntroToOpenGL/src/main.cpp > CMakeFiles/ITOG.dir/src/main.cpp.i

CMakeFiles/ITOG.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITOG.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leo/code/IntroToOpenGL/src/main.cpp -o CMakeFiles/ITOG.dir/src/main.cpp.s

CMakeFiles/ITOG.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/ITOG.dir/src/main.cpp.o.requires

CMakeFiles/ITOG.dir/src/main.cpp.o.provides: CMakeFiles/ITOG.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ITOG.dir/build.make CMakeFiles/ITOG.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/ITOG.dir/src/main.cpp.o.provides

CMakeFiles/ITOG.dir/src/main.cpp.o.provides.build: CMakeFiles/ITOG.dir/src/main.cpp.o


# Object files for target ITOG
ITOG_OBJECTS = \
"CMakeFiles/ITOG.dir/src/main.cpp.o"

# External object files for target ITOG
ITOG_EXTERNAL_OBJECTS =

ITOG: CMakeFiles/ITOG.dir/src/main.cpp.o
ITOG: CMakeFiles/ITOG.dir/build.make
ITOG: /usr/lib/x86_64-linux-gnu/libGL.so
ITOG: /usr/lib/x86_64-linux-gnu/libGLU.so
ITOG: /usr/lib/x86_64-linux-gnu/libGLEW.so
ITOG: /usr/lib/x86_64-linux-gnu/libSDL2.so
ITOG: /usr/lib/x86_64-linux-gnu/libassimp.so
ITOG: CMakeFiles/ITOG.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leo/code/IntroToOpenGL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ITOG"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ITOG.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ITOG.dir/build: ITOG

.PHONY : CMakeFiles/ITOG.dir/build

CMakeFiles/ITOG.dir/requires: CMakeFiles/ITOG.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/ITOG.dir/requires

CMakeFiles/ITOG.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ITOG.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ITOG.dir/clean

CMakeFiles/ITOG.dir/depend:
	cd /home/leo/code/IntroToOpenGL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leo/code/IntroToOpenGL /home/leo/code/IntroToOpenGL /home/leo/code/IntroToOpenGL/build /home/leo/code/IntroToOpenGL/build /home/leo/code/IntroToOpenGL/build/CMakeFiles/ITOG.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ITOG.dir/depend
