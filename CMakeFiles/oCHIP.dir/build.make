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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gab/projects/CHIP8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gab/projects/CHIP8

# Include any dependencies generated for this target.
include CMakeFiles/oCHIP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/oCHIP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/oCHIP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/oCHIP.dir/flags.make

CMakeFiles/oCHIP.dir/CHIP8.cpp.o: CMakeFiles/oCHIP.dir/flags.make
CMakeFiles/oCHIP.dir/CHIP8.cpp.o: CHIP8.cpp
CMakeFiles/oCHIP.dir/CHIP8.cpp.o: CMakeFiles/oCHIP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gab/projects/CHIP8/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/oCHIP.dir/CHIP8.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oCHIP.dir/CHIP8.cpp.o -MF CMakeFiles/oCHIP.dir/CHIP8.cpp.o.d -o CMakeFiles/oCHIP.dir/CHIP8.cpp.o -c /home/gab/projects/CHIP8/CHIP8.cpp

CMakeFiles/oCHIP.dir/CHIP8.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oCHIP.dir/CHIP8.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gab/projects/CHIP8/CHIP8.cpp > CMakeFiles/oCHIP.dir/CHIP8.cpp.i

CMakeFiles/oCHIP.dir/CHIP8.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oCHIP.dir/CHIP8.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gab/projects/CHIP8/CHIP8.cpp -o CMakeFiles/oCHIP.dir/CHIP8.cpp.s

CMakeFiles/oCHIP.dir/opcodes.cpp.o: CMakeFiles/oCHIP.dir/flags.make
CMakeFiles/oCHIP.dir/opcodes.cpp.o: opcodes.cpp
CMakeFiles/oCHIP.dir/opcodes.cpp.o: CMakeFiles/oCHIP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gab/projects/CHIP8/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/oCHIP.dir/opcodes.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oCHIP.dir/opcodes.cpp.o -MF CMakeFiles/oCHIP.dir/opcodes.cpp.o.d -o CMakeFiles/oCHIP.dir/opcodes.cpp.o -c /home/gab/projects/CHIP8/opcodes.cpp

CMakeFiles/oCHIP.dir/opcodes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/oCHIP.dir/opcodes.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gab/projects/CHIP8/opcodes.cpp > CMakeFiles/oCHIP.dir/opcodes.cpp.i

CMakeFiles/oCHIP.dir/opcodes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/oCHIP.dir/opcodes.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gab/projects/CHIP8/opcodes.cpp -o CMakeFiles/oCHIP.dir/opcodes.cpp.s

# Object files for target oCHIP
oCHIP_OBJECTS = \
"CMakeFiles/oCHIP.dir/CHIP8.cpp.o" \
"CMakeFiles/oCHIP.dir/opcodes.cpp.o"

# External object files for target oCHIP
oCHIP_EXTERNAL_OBJECTS =

oCHIP: CMakeFiles/oCHIP.dir/CHIP8.cpp.o
oCHIP: CMakeFiles/oCHIP.dir/opcodes.cpp.o
oCHIP: CMakeFiles/oCHIP.dir/build.make
oCHIP: CMakeFiles/oCHIP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gab/projects/CHIP8/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable oCHIP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oCHIP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/oCHIP.dir/build: oCHIP
.PHONY : CMakeFiles/oCHIP.dir/build

CMakeFiles/oCHIP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/oCHIP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/oCHIP.dir/clean

CMakeFiles/oCHIP.dir/depend:
	cd /home/gab/projects/CHIP8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gab/projects/CHIP8 /home/gab/projects/CHIP8 /home/gab/projects/CHIP8 /home/gab/projects/CHIP8 /home/gab/projects/CHIP8/CMakeFiles/oCHIP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/oCHIP.dir/depend

