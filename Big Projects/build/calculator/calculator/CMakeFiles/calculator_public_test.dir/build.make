# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = "/home/sergey_kornienko/Programming/Big Projects"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/sergey_kornienko/Programming/Big Projects/build"

# Include any dependencies generated for this target.
include calculator/calculator/CMakeFiles/calculator_public_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include calculator/calculator/CMakeFiles/calculator_public_test.dir/compiler_depend.make

# Include the progress variables for this target.
include calculator/calculator/CMakeFiles/calculator_public_test.dir/progress.make

# Include the compile flags for this target's objects.
include calculator/calculator/CMakeFiles/calculator_public_test.dir/flags.make

calculator/calculator/CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o: calculator/calculator/CMakeFiles/calculator_public_test.dir/flags.make
calculator/calculator/CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o: ../calculator/tokenize/tokenize.cpp
calculator/calculator/CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o: calculator/calculator/CMakeFiles/calculator_public_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sergey_kornienko/Programming/Big Projects/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object calculator/calculator/CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT calculator/calculator/CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o -MF CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o.d -o CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o -c "/home/sergey_kornienko/Programming/Big Projects/calculator/tokenize/tokenize.cpp"

calculator/calculator/CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.i"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sergey_kornienko/Programming/Big Projects/calculator/tokenize/tokenize.cpp" > CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.i

calculator/calculator/CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.s"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sergey_kornienko/Programming/Big Projects/calculator/tokenize/tokenize.cpp" -o CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.s

calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator.cpp.o: calculator/calculator/CMakeFiles/calculator_public_test.dir/flags.make
calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator.cpp.o: ../calculator/calculator/calculator.cpp
calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator.cpp.o: calculator/calculator/CMakeFiles/calculator_public_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sergey_kornienko/Programming/Big Projects/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator.cpp.o"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator.cpp.o -MF CMakeFiles/calculator_public_test.dir/calculator.cpp.o.d -o CMakeFiles/calculator_public_test.dir/calculator.cpp.o -c "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/calculator.cpp"

calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator_public_test.dir/calculator.cpp.i"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/calculator.cpp" > CMakeFiles/calculator_public_test.dir/calculator.cpp.i

calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator_public_test.dir/calculator.cpp.s"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/calculator.cpp" -o CMakeFiles/calculator_public_test.dir/calculator.cpp.s

calculator/calculator/CMakeFiles/calculator_public_test.dir/parser.cpp.o: calculator/calculator/CMakeFiles/calculator_public_test.dir/flags.make
calculator/calculator/CMakeFiles/calculator_public_test.dir/parser.cpp.o: ../calculator/calculator/parser.cpp
calculator/calculator/CMakeFiles/calculator_public_test.dir/parser.cpp.o: calculator/calculator/CMakeFiles/calculator_public_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sergey_kornienko/Programming/Big Projects/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object calculator/calculator/CMakeFiles/calculator_public_test.dir/parser.cpp.o"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT calculator/calculator/CMakeFiles/calculator_public_test.dir/parser.cpp.o -MF CMakeFiles/calculator_public_test.dir/parser.cpp.o.d -o CMakeFiles/calculator_public_test.dir/parser.cpp.o -c "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/parser.cpp"

calculator/calculator/CMakeFiles/calculator_public_test.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator_public_test.dir/parser.cpp.i"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/parser.cpp" > CMakeFiles/calculator_public_test.dir/parser.cpp.i

calculator/calculator/CMakeFiles/calculator_public_test.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator_public_test.dir/parser.cpp.s"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/parser.cpp" -o CMakeFiles/calculator_public_test.dir/parser.cpp.s

calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o: calculator/calculator/CMakeFiles/calculator_public_test.dir/flags.make
calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o: ../calculator/calculator/calculator_public_test.cpp
calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o: calculator/calculator/CMakeFiles/calculator_public_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sergey_kornienko/Programming/Big Projects/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o -MF CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o.d -o CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o -c "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/calculator_public_test.cpp"

calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.i"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/calculator_public_test.cpp" > CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.i

calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.s"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator/calculator_public_test.cpp" -o CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.s

# Object files for target calculator_public_test
calculator_public_test_OBJECTS = \
"CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o" \
"CMakeFiles/calculator_public_test.dir/calculator.cpp.o" \
"CMakeFiles/calculator_public_test.dir/parser.cpp.o" \
"CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o"

# External object files for target calculator_public_test
calculator_public_test_EXTERNAL_OBJECTS =

calculator_public_test: calculator/calculator/CMakeFiles/calculator_public_test.dir/__/tokenize/tokenize.cpp.o
calculator_public_test: calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator.cpp.o
calculator_public_test: calculator/calculator/CMakeFiles/calculator_public_test.dir/parser.cpp.o
calculator_public_test: calculator/calculator/CMakeFiles/calculator_public_test.dir/calculator_public_test.cpp.o
calculator_public_test: calculator/calculator/CMakeFiles/calculator_public_test.dir/build.make
calculator_public_test: calculator/calculator/CMakeFiles/calculator_public_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/sergey_kornienko/Programming/Big Projects/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../../calculator_public_test"
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/calculator_public_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
calculator/calculator/CMakeFiles/calculator_public_test.dir/build: calculator_public_test
.PHONY : calculator/calculator/CMakeFiles/calculator_public_test.dir/build

calculator/calculator/CMakeFiles/calculator_public_test.dir/clean:
	cd "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" && $(CMAKE_COMMAND) -P CMakeFiles/calculator_public_test.dir/cmake_clean.cmake
.PHONY : calculator/calculator/CMakeFiles/calculator_public_test.dir/clean

calculator/calculator/CMakeFiles/calculator_public_test.dir/depend:
	cd "/home/sergey_kornienko/Programming/Big Projects/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/sergey_kornienko/Programming/Big Projects" "/home/sergey_kornienko/Programming/Big Projects/calculator/calculator" "/home/sergey_kornienko/Programming/Big Projects/build" "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator" "/home/sergey_kornienko/Programming/Big Projects/build/calculator/calculator/CMakeFiles/calculator_public_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : calculator/calculator/CMakeFiles/calculator_public_test.dir/depend

