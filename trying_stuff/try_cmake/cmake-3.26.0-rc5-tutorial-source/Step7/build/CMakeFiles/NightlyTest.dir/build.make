# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/davidnakasone/Desktop/sandBox/trying_stuff/try_cmake/cmake-3.26.0-rc5-tutorial-source/Step7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/davidnakasone/Desktop/sandBox/trying_stuff/try_cmake/cmake-3.26.0-rc5-tutorial-source/Step7/build

# Utility rule file for NightlyTest.

# Include any custom commands dependencies for this target.
include CMakeFiles/NightlyTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/NightlyTest.dir/progress.make

CMakeFiles/NightlyTest:
	/usr/local/Cellar/cmake/3.25.2/bin/ctest -D NightlyTest

NightlyTest: CMakeFiles/NightlyTest
NightlyTest: CMakeFiles/NightlyTest.dir/build.make
.PHONY : NightlyTest

# Rule to build all files generated by this target.
CMakeFiles/NightlyTest.dir/build: NightlyTest
.PHONY : CMakeFiles/NightlyTest.dir/build

CMakeFiles/NightlyTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NightlyTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NightlyTest.dir/clean

CMakeFiles/NightlyTest.dir/depend:
	cd /Users/davidnakasone/Desktop/sandBox/trying_stuff/try_cmake/cmake-3.26.0-rc5-tutorial-source/Step7/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/davidnakasone/Desktop/sandBox/trying_stuff/try_cmake/cmake-3.26.0-rc5-tutorial-source/Step7 /Users/davidnakasone/Desktop/sandBox/trying_stuff/try_cmake/cmake-3.26.0-rc5-tutorial-source/Step7 /Users/davidnakasone/Desktop/sandBox/trying_stuff/try_cmake/cmake-3.26.0-rc5-tutorial-source/Step7/build /Users/davidnakasone/Desktop/sandBox/trying_stuff/try_cmake/cmake-3.26.0-rc5-tutorial-source/Step7/build /Users/davidnakasone/Desktop/sandBox/trying_stuff/try_cmake/cmake-3.26.0-rc5-tutorial-source/Step7/build/CMakeFiles/NightlyTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NightlyTest.dir/depend

