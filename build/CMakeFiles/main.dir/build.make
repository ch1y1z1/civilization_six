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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yankun/c++zuoye/civilization_six/civilization_six

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yankun/c++zuoye/civilization_six/civilization_six/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: /Users/yankun/c++zuoye/civilization_six/civilization_six/main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yankun/c++zuoye/civilization_six/civilization_six/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /Users/yankun/c++zuoye/civilization_six/civilization_six/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yankun/c++zuoye/civilization_six/civilization_six/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yankun/c++zuoye/civilization_six/civilization_six/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/src/Activity.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Activity.cpp.o: /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Activity.cpp
CMakeFiles/main.dir/src/Activity.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yankun/c++zuoye/civilization_six/civilization_six/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/Activity.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Activity.cpp.o -MF CMakeFiles/main.dir/src/Activity.cpp.o.d -o CMakeFiles/main.dir/src/Activity.cpp.o -c /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Activity.cpp

CMakeFiles/main.dir/src/Activity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Activity.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Activity.cpp > CMakeFiles/main.dir/src/Activity.cpp.i

CMakeFiles/main.dir/src/Activity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Activity.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Activity.cpp -o CMakeFiles/main.dir/src/Activity.cpp.s

CMakeFiles/main.dir/src/Building.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Building.cpp.o: /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Building.cpp
CMakeFiles/main.dir/src/Building.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yankun/c++zuoye/civilization_six/civilization_six/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/Building.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Building.cpp.o -MF CMakeFiles/main.dir/src/Building.cpp.o.d -o CMakeFiles/main.dir/src/Building.cpp.o -c /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Building.cpp

CMakeFiles/main.dir/src/Building.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Building.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Building.cpp > CMakeFiles/main.dir/src/Building.cpp.i

CMakeFiles/main.dir/src/Building.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Building.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Building.cpp -o CMakeFiles/main.dir/src/Building.cpp.s

CMakeFiles/main.dir/src/Controller.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Controller.cpp.o: /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Controller.cpp
CMakeFiles/main.dir/src/Controller.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yankun/c++zuoye/civilization_six/civilization_six/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/src/Controller.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Controller.cpp.o -MF CMakeFiles/main.dir/src/Controller.cpp.o.d -o CMakeFiles/main.dir/src/Controller.cpp.o -c /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Controller.cpp

CMakeFiles/main.dir/src/Controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Controller.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Controller.cpp > CMakeFiles/main.dir/src/Controller.cpp.i

CMakeFiles/main.dir/src/Controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Controller.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Controller.cpp -o CMakeFiles/main.dir/src/Controller.cpp.s

CMakeFiles/main.dir/src/Display.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Display.cpp.o: /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Display.cpp
CMakeFiles/main.dir/src/Display.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yankun/c++zuoye/civilization_six/civilization_six/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/src/Display.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Display.cpp.o -MF CMakeFiles/main.dir/src/Display.cpp.o.d -o CMakeFiles/main.dir/src/Display.cpp.o -c /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Display.cpp

CMakeFiles/main.dir/src/Display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Display.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Display.cpp > CMakeFiles/main.dir/src/Display.cpp.i

CMakeFiles/main.dir/src/Display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Display.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Display.cpp -o CMakeFiles/main.dir/src/Display.cpp.s

CMakeFiles/main.dir/src/Grid.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/Grid.cpp.o: /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Grid.cpp
CMakeFiles/main.dir/src/Grid.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yankun/c++zuoye/civilization_six/civilization_six/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/src/Grid.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/Grid.cpp.o -MF CMakeFiles/main.dir/src/Grid.cpp.o.d -o CMakeFiles/main.dir/src/Grid.cpp.o -c /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Grid.cpp

CMakeFiles/main.dir/src/Grid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/Grid.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Grid.cpp > CMakeFiles/main.dir/src/Grid.cpp.i

CMakeFiles/main.dir/src/Grid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/Grid.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yankun/c++zuoye/civilization_six/civilization_six/src/Grid.cpp -o CMakeFiles/main.dir/src/Grid.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/src/Activity.cpp.o" \
"CMakeFiles/main.dir/src/Building.cpp.o" \
"CMakeFiles/main.dir/src/Controller.cpp.o" \
"CMakeFiles/main.dir/src/Display.cpp.o" \
"CMakeFiles/main.dir/src/Grid.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/src/Activity.cpp.o
main: CMakeFiles/main.dir/src/Building.cpp.o
main: CMakeFiles/main.dir/src/Controller.cpp.o
main: CMakeFiles/main.dir/src/Display.cpp.o
main: CMakeFiles/main.dir/src/Grid.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/yankun/c++zuoye/civilization_six/civilization_six/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /Users/yankun/c++zuoye/civilization_six/civilization_six/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yankun/c++zuoye/civilization_six/civilization_six /Users/yankun/c++zuoye/civilization_six/civilization_six /Users/yankun/c++zuoye/civilization_six/civilization_six/build /Users/yankun/c++zuoye/civilization_six/civilization_six/build /Users/yankun/c++zuoye/civilization_six/civilization_six/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend
