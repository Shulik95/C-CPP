# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/user/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/user/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/user/CLionProjects/c_exam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/user/CLionProjects/c_exam/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/c_exam.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/c_exam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/c_exam.dir/flags.make

CMakeFiles/c_exam.dir/main.cpp.o: CMakeFiles/c_exam.dir/flags.make
CMakeFiles/c_exam.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/user/CLionProjects/c_exam/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/c_exam.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/c_exam.dir/main.cpp.o -c /cygdrive/c/Users/user/CLionProjects/c_exam/main.cpp

CMakeFiles/c_exam.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/c_exam.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/user/CLionProjects/c_exam/main.cpp > CMakeFiles/c_exam.dir/main.cpp.i

CMakeFiles/c_exam.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/c_exam.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/user/CLionProjects/c_exam/main.cpp -o CMakeFiles/c_exam.dir/main.cpp.s

# Object files for target c_exam
c_exam_OBJECTS = \
"CMakeFiles/c_exam.dir/main.cpp.o"

# External object files for target c_exam
c_exam_EXTERNAL_OBJECTS =

c_exam.exe: CMakeFiles/c_exam.dir/main.cpp.o
c_exam.exe: CMakeFiles/c_exam.dir/build.make
c_exam.exe: CMakeFiles/c_exam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/user/CLionProjects/c_exam/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable c_exam.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/c_exam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/c_exam.dir/build: c_exam.exe

.PHONY : CMakeFiles/c_exam.dir/build

CMakeFiles/c_exam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/c_exam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/c_exam.dir/clean

CMakeFiles/c_exam.dir/depend:
	cd /cygdrive/c/Users/user/CLionProjects/c_exam/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/user/CLionProjects/c_exam /cygdrive/c/Users/user/CLionProjects/c_exam /cygdrive/c/Users/user/CLionProjects/c_exam/cmake-build-debug /cygdrive/c/Users/user/CLionProjects/c_exam/cmake-build-debug /cygdrive/c/Users/user/CLionProjects/c_exam/cmake-build-debug/CMakeFiles/c_exam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/c_exam.dir/depend

