# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vagrant/AutoMoDe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vagrant/AutoMoDe/build

# Utility rule file for automode_main_automoc.

# Include the progress variables for this target.
include src/CMakeFiles/automode_main_automoc.dir/progress.make

src/CMakeFiles/automode_main_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vagrant/AutoMoDe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc for target automode_main"
	cd /home/vagrant/AutoMoDe/build/src && /usr/local/bin/cmake -E cmake_autogen /home/vagrant/AutoMoDe/build/src/CMakeFiles/automode_main_automoc.dir/ ""

automode_main_automoc: src/CMakeFiles/automode_main_automoc
automode_main_automoc: src/CMakeFiles/automode_main_automoc.dir/build.make

.PHONY : automode_main_automoc

# Rule to build all files generated by this target.
src/CMakeFiles/automode_main_automoc.dir/build: automode_main_automoc

.PHONY : src/CMakeFiles/automode_main_automoc.dir/build

src/CMakeFiles/automode_main_automoc.dir/clean:
	cd /home/vagrant/AutoMoDe/build/src && $(CMAKE_COMMAND) -P CMakeFiles/automode_main_automoc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/automode_main_automoc.dir/clean

src/CMakeFiles/automode_main_automoc.dir/depend:
	cd /home/vagrant/AutoMoDe/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/AutoMoDe /home/vagrant/AutoMoDe/src /home/vagrant/AutoMoDe/build /home/vagrant/AutoMoDe/build/src /home/vagrant/AutoMoDe/build/src/CMakeFiles/automode_main_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/automode_main_automoc.dir/depend

