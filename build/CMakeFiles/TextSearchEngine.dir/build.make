# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /workspaces/Yat-Search-Engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/Yat-Search-Engine/build

# Include any dependencies generated for this target.
include CMakeFiles/TextSearchEngine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TextSearchEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TextSearchEngine.dir/flags.make

CMakeFiles/TextSearchEngine.dir/src/main.cpp.o: CMakeFiles/TextSearchEngine.dir/flags.make
CMakeFiles/TextSearchEngine.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/Yat-Search-Engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TextSearchEngine.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TextSearchEngine.dir/src/main.cpp.o -c /workspaces/Yat-Search-Engine/src/main.cpp

CMakeFiles/TextSearchEngine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TextSearchEngine.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/Yat-Search-Engine/src/main.cpp > CMakeFiles/TextSearchEngine.dir/src/main.cpp.i

CMakeFiles/TextSearchEngine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TextSearchEngine.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/Yat-Search-Engine/src/main.cpp -o CMakeFiles/TextSearchEngine.dir/src/main.cpp.s

CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.o: CMakeFiles/TextSearchEngine.dir/flags.make
CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.o: ../src/TextSearchEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/Yat-Search-Engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.o -c /workspaces/Yat-Search-Engine/src/TextSearchEngine.cpp

CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/Yat-Search-Engine/src/TextSearchEngine.cpp > CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.i

CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/Yat-Search-Engine/src/TextSearchEngine.cpp -o CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.s

CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.o: CMakeFiles/TextSearchEngine.dir/flags.make
CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.o: ../src/RegexSearch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/Yat-Search-Engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.o -c /workspaces/Yat-Search-Engine/src/RegexSearch.cpp

CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/Yat-Search-Engine/src/RegexSearch.cpp > CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.i

CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/Yat-Search-Engine/src/RegexSearch.cpp -o CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.s

# Object files for target TextSearchEngine
TextSearchEngine_OBJECTS = \
"CMakeFiles/TextSearchEngine.dir/src/main.cpp.o" \
"CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.o" \
"CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.o"

# External object files for target TextSearchEngine
TextSearchEngine_EXTERNAL_OBJECTS =

TextSearchEngine: CMakeFiles/TextSearchEngine.dir/src/main.cpp.o
TextSearchEngine: CMakeFiles/TextSearchEngine.dir/src/TextSearchEngine.cpp.o
TextSearchEngine: CMakeFiles/TextSearchEngine.dir/src/RegexSearch.cpp.o
TextSearchEngine: CMakeFiles/TextSearchEngine.dir/build.make
TextSearchEngine: CMakeFiles/TextSearchEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/Yat-Search-Engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable TextSearchEngine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TextSearchEngine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TextSearchEngine.dir/build: TextSearchEngine

.PHONY : CMakeFiles/TextSearchEngine.dir/build

CMakeFiles/TextSearchEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TextSearchEngine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TextSearchEngine.dir/clean

CMakeFiles/TextSearchEngine.dir/depend:
	cd /workspaces/Yat-Search-Engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/Yat-Search-Engine /workspaces/Yat-Search-Engine /workspaces/Yat-Search-Engine/build /workspaces/Yat-Search-Engine/build /workspaces/Yat-Search-Engine/build/CMakeFiles/TextSearchEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TextSearchEngine.dir/depend

