# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\savmo\Documents\Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\savmo\Documents\Client\cmake-build-debug-qtcmake

# Utility rule file for DataProtocol_autogen.

# Include the progress variables for this target.
include src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/progress.make

src/DataProtocol/CMakeFiles/DataProtocol_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\savmo\Documents\Client\cmake-build-debug-qtcmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target DataProtocol"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-debug-qtcmake\src\DataProtocol && C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E cmake_autogen C:/Users/savmo/Documents/Client/cmake-build-debug-qtcmake/src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/AutogenInfo.json Debug

DataProtocol_autogen: src/DataProtocol/CMakeFiles/DataProtocol_autogen
DataProtocol_autogen: src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/build.make

.PHONY : DataProtocol_autogen

# Rule to build all files generated by this target.
src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/build: DataProtocol_autogen

.PHONY : src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/build

src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/clean:
	cd /d C:\Users\savmo\Documents\Client\cmake-build-debug-qtcmake\src\DataProtocol && $(CMAKE_COMMAND) -P CMakeFiles\DataProtocol_autogen.dir\cmake_clean.cmake
.PHONY : src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/clean

src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\savmo\Documents\Client C:\Users\savmo\Documents\Client\src\DataProtocol C:\Users\savmo\Documents\Client\cmake-build-debug-qtcmake C:\Users\savmo\Documents\Client\cmake-build-debug-qtcmake\src\DataProtocol C:\Users\savmo\Documents\Client\cmake-build-debug-qtcmake\src\DataProtocol\CMakeFiles\DataProtocol_autogen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/DataProtocol/CMakeFiles/DataProtocol_autogen.dir/depend

