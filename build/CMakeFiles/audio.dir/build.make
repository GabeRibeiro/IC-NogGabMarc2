# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/marcoramos/Desktop/IC-NogGabMarc2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcoramos/Desktop/IC-NogGabMarc2/build

# Include any dependencies generated for this target.
include CMakeFiles/audio.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/audio.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/audio.dir/flags.make

CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o: CMakeFiles/audio.dir/flags.make
CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o: ../src/audio/AudioCodec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcoramos/Desktop/IC-NogGabMarc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o -c /home/marcoramos/Desktop/IC-NogGabMarc2/src/audio/AudioCodec.cpp

CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcoramos/Desktop/IC-NogGabMarc2/src/audio/AudioCodec.cpp > CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.i

CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcoramos/Desktop/IC-NogGabMarc2/src/audio/AudioCodec.cpp -o CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.s

CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o.requires:

.PHONY : CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o.requires

CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o.provides: CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o.requires
	$(MAKE) -f CMakeFiles/audio.dir/build.make CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o.provides.build
.PHONY : CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o.provides

CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o.provides.build: CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o


# Object files for target audio
audio_OBJECTS = \
"CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o"

# External object files for target audio
audio_EXTERNAL_OBJECTS =

libaudio.a: CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o
libaudio.a: CMakeFiles/audio.dir/build.make
libaudio.a: CMakeFiles/audio.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcoramos/Desktop/IC-NogGabMarc2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libaudio.a"
	$(CMAKE_COMMAND) -P CMakeFiles/audio.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/audio.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/audio.dir/build: libaudio.a

.PHONY : CMakeFiles/audio.dir/build

CMakeFiles/audio.dir/requires: CMakeFiles/audio.dir/src/audio/AudioCodec.cpp.o.requires

.PHONY : CMakeFiles/audio.dir/requires

CMakeFiles/audio.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/audio.dir/cmake_clean.cmake
.PHONY : CMakeFiles/audio.dir/clean

CMakeFiles/audio.dir/depend:
	cd /home/marcoramos/Desktop/IC-NogGabMarc2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcoramos/Desktop/IC-NogGabMarc2 /home/marcoramos/Desktop/IC-NogGabMarc2 /home/marcoramos/Desktop/IC-NogGabMarc2/build /home/marcoramos/Desktop/IC-NogGabMarc2/build /home/marcoramos/Desktop/IC-NogGabMarc2/build/CMakeFiles/audio.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/audio.dir/depend

