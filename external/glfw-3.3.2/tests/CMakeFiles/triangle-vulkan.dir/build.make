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
CMAKE_SOURCE_DIR = /home/nathan/projects/c++/TardigradeRenderEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nathan/projects/c++/TardigradeRenderEngine

# Include any dependencies generated for this target.
include external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/depend.make

# Include the progress variables for this target.
include external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/flags.make

external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/flags.make
external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: external/glfw-3.3.2/tests/triangle-vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nathan/projects/c++/TardigradeRenderEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o"
	cd /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o   -c /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests/triangle-vulkan.c

external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i"
	cd /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests/triangle-vulkan.c > CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i

external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s"
	cd /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests/triangle-vulkan.c -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s

external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/flags.make
external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: external/glfw-3.3.2/deps/glad_vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nathan/projects/c++/TardigradeRenderEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"
	cd /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o   -c /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/deps/glad_vulkan.c

external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i"
	cd /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/deps/glad_vulkan.c > CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i

external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s"
	cd /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/deps/glad_vulkan.c -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s

# Object files for target triangle-vulkan
triangle__vulkan_OBJECTS = \
"CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o" \
"CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"

# External object files for target triangle-vulkan
triangle__vulkan_EXTERNAL_OBJECTS =

external/glfw-3.3.2/tests/triangle-vulkan: external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o
external/glfw-3.3.2/tests/triangle-vulkan: external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o
external/glfw-3.3.2/tests/triangle-vulkan: external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/build.make
external/glfw-3.3.2/tests/triangle-vulkan: external/glfw-3.3.2/src/libglfw3.a
external/glfw-3.3.2/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.3.2/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/librt.so
external/glfw-3.3.2/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.3.2/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libX11.so
external/glfw-3.3.2/tests/triangle-vulkan: external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nathan/projects/c++/TardigradeRenderEngine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable triangle-vulkan"
	cd /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle-vulkan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/build: external/glfw-3.3.2/tests/triangle-vulkan

.PHONY : external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/build

external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/clean:
	cd /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests && $(CMAKE_COMMAND) -P CMakeFiles/triangle-vulkan.dir/cmake_clean.cmake
.PHONY : external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/clean

external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/depend:
	cd /home/nathan/projects/c++/TardigradeRenderEngine && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nathan/projects/c++/TardigradeRenderEngine /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests /home/nathan/projects/c++/TardigradeRenderEngine /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests /home/nathan/projects/c++/TardigradeRenderEngine/external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.3.2/tests/CMakeFiles/triangle-vulkan.dir/depend

