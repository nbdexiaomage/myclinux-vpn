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
CMAKE_SOURCE_DIR = /home/mycroot/ccode/TCPIP/ch1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mycroot/ccode/TCPIP/ch1/build

# Include any dependencies generated for this target.
include CMakeFiles/demo01.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/demo01.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/demo01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo01.dir/flags.make

CMakeFiles/demo01.dir/src/hello_client.c.o: CMakeFiles/demo01.dir/flags.make
CMakeFiles/demo01.dir/src/hello_client.c.o: ../src/hello_client.c
CMakeFiles/demo01.dir/src/hello_client.c.o: CMakeFiles/demo01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mycroot/ccode/TCPIP/ch1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/demo01.dir/src/hello_client.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/demo01.dir/src/hello_client.c.o -MF CMakeFiles/demo01.dir/src/hello_client.c.o.d -o CMakeFiles/demo01.dir/src/hello_client.c.o -c /home/mycroot/ccode/TCPIP/ch1/src/hello_client.c

CMakeFiles/demo01.dir/src/hello_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/demo01.dir/src/hello_client.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mycroot/ccode/TCPIP/ch1/src/hello_client.c > CMakeFiles/demo01.dir/src/hello_client.c.i

CMakeFiles/demo01.dir/src/hello_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/demo01.dir/src/hello_client.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mycroot/ccode/TCPIP/ch1/src/hello_client.c -o CMakeFiles/demo01.dir/src/hello_client.c.s

CMakeFiles/demo01.dir/src/hello_server.c.o: CMakeFiles/demo01.dir/flags.make
CMakeFiles/demo01.dir/src/hello_server.c.o: ../src/hello_server.c
CMakeFiles/demo01.dir/src/hello_server.c.o: CMakeFiles/demo01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mycroot/ccode/TCPIP/ch1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/demo01.dir/src/hello_server.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/demo01.dir/src/hello_server.c.o -MF CMakeFiles/demo01.dir/src/hello_server.c.o.d -o CMakeFiles/demo01.dir/src/hello_server.c.o -c /home/mycroot/ccode/TCPIP/ch1/src/hello_server.c

CMakeFiles/demo01.dir/src/hello_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/demo01.dir/src/hello_server.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mycroot/ccode/TCPIP/ch1/src/hello_server.c > CMakeFiles/demo01.dir/src/hello_server.c.i

CMakeFiles/demo01.dir/src/hello_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/demo01.dir/src/hello_server.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mycroot/ccode/TCPIP/ch1/src/hello_server.c -o CMakeFiles/demo01.dir/src/hello_server.c.s

# Object files for target demo01
demo01_OBJECTS = \
"CMakeFiles/demo01.dir/src/hello_client.c.o" \
"CMakeFiles/demo01.dir/src/hello_server.c.o"

# External object files for target demo01
demo01_EXTERNAL_OBJECTS =

demo01: CMakeFiles/demo01.dir/src/hello_client.c.o
demo01: CMakeFiles/demo01.dir/src/hello_server.c.o
demo01: CMakeFiles/demo01.dir/build.make
demo01: CMakeFiles/demo01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mycroot/ccode/TCPIP/ch1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable demo01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo01.dir/build: demo01
.PHONY : CMakeFiles/demo01.dir/build

CMakeFiles/demo01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo01.dir/clean

CMakeFiles/demo01.dir/depend:
	cd /home/mycroot/ccode/TCPIP/ch1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mycroot/ccode/TCPIP/ch1 /home/mycroot/ccode/TCPIP/ch1 /home/mycroot/ccode/TCPIP/ch1/build /home/mycroot/ccode/TCPIP/ch1/build /home/mycroot/ccode/TCPIP/ch1/build/CMakeFiles/demo01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo01.dir/depend

