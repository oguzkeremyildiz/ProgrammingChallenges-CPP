# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProgrammingChallenges_CPP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProgrammingChallenges_CPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProgrammingChallenges_CPP.dir/flags.make

CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.o: CMakeFiles/ProgrammingChallenges_CPP.dir/flags.make
CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.o: ../DynamicProgramming/D2/DistinctSubsequences.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.o -c /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/DynamicProgramming/D2/DistinctSubsequences.cpp

CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/DynamicProgramming/D2/DistinctSubsequences.cpp > CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.i

CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/DynamicProgramming/D2/DistinctSubsequences.cpp -o CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.s

# Object files for target ProgrammingChallenges_CPP
ProgrammingChallenges_CPP_OBJECTS = \
"CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.o"

# External object files for target ProgrammingChallenges_CPP
ProgrammingChallenges_CPP_EXTERNAL_OBJECTS =

ProgrammingChallenges_CPP: CMakeFiles/ProgrammingChallenges_CPP.dir/DynamicProgramming/D2/DistinctSubsequences.cpp.o
ProgrammingChallenges_CPP: CMakeFiles/ProgrammingChallenges_CPP.dir/build.make
ProgrammingChallenges_CPP: CMakeFiles/ProgrammingChallenges_CPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ProgrammingChallenges_CPP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProgrammingChallenges_CPP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProgrammingChallenges_CPP.dir/build: ProgrammingChallenges_CPP

.PHONY : CMakeFiles/ProgrammingChallenges_CPP.dir/build

CMakeFiles/ProgrammingChallenges_CPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProgrammingChallenges_CPP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProgrammingChallenges_CPP.dir/clean

CMakeFiles/ProgrammingChallenges_CPP.dir/depend:
	cd /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/cmake-build-debug /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/cmake-build-debug /Users/oguzkeremyildiz/Dropbox/ProgrammingChallenges-CPP/cmake-build-debug/CMakeFiles/ProgrammingChallenges_CPP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProgrammingChallenges_CPP.dir/depend

