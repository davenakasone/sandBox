#[[
    https://cmake.org/cmake/help/book/mastering-cmake/chapter/Getting%20Started.html

    1) make a directory for the binaries to go
    2) move into the binary directory
    3) run 'cmake' specifying path to source tree
    4) run 'make'
]]

# first line in top-level is version, requires project to be at least this + backward compatible
cmake_minimum_required(VERSION 3.20)

# set the name of the project and may specify other options such as language or version
#[[
    For each directory in a project where the CMakeLists.txt file invokes the project command, 
    CMake generates a top-level Makefile or IDE project file. 
    The project will contain all targets that are in the CMakeLists.txt file and any subdirectories, 
    as specified by the add_subdirectory command. 
    If the EXCLUDE_FROM_ALL option is used in the add_subdirectory command, 
    the generated project will not appear in the top-level Makefile or IDE project file; 
    this is useful for generating sub-projects that do not make sense as part of the main build process. 
    Consider that a project with a number of examples could use this feature to generate the build files 
    for each example with one run of CMake, but not have the examples built as part of the normal build process.
]]
project(test)

# add an executable to the project using the given source file
add_executable(test test.c)


########~~~~~~~~END>  CMakeLists.txt
