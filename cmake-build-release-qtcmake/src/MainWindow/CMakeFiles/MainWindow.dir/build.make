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
CMAKE_BINARY_DIR = C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake

# Include any dependencies generated for this target.
include src/MainWindow/CMakeFiles/MainWindow.dir/depend.make

# Include the progress variables for this target.
include src/MainWindow/CMakeFiles/MainWindow.dir/progress.make

# Include the compile flags for this target's objects.
include src/MainWindow/CMakeFiles/MainWindow.dir/flags.make

src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.obj: src/MainWindow/CMakeFiles/MainWindow.dir/flags.make
src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.obj: src/MainWindow/CMakeFiles/MainWindow.dir/includes_CXX.rsp
src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.obj: src/MainWindow/MainWindow_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.obj"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && C:/Users/savmo/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/211.7442.42/bin/cmake/win/bin/cmake.exe -E time C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MainWindow.dir\MainWindow_autogen\mocs_compilation.cpp.obj -c C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow\MainWindow_autogen\mocs_compilation.cpp

src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.i"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow\MainWindow_autogen\mocs_compilation.cpp > CMakeFiles\MainWindow.dir\MainWindow_autogen\mocs_compilation.cpp.i

src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.s"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow\MainWindow_autogen\mocs_compilation.cpp -o CMakeFiles\MainWindow.dir\MainWindow_autogen\mocs_compilation.cpp.s

src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow.cpp.obj: src/MainWindow/CMakeFiles/MainWindow.dir/flags.make
src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow.cpp.obj: src/MainWindow/CMakeFiles/MainWindow.dir/includes_CXX.rsp
src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow.cpp.obj: ../src/MainWindow/MainWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow.cpp.obj"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && C:/Users/savmo/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/211.7442.42/bin/cmake/win/bin/cmake.exe -E time C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MainWindow.dir\MainWindow.cpp.obj -c C:\Users\savmo\Documents\Client\src\MainWindow\MainWindow.cpp

src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainWindow.dir/MainWindow.cpp.i"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\savmo\Documents\Client\src\MainWindow\MainWindow.cpp > CMakeFiles\MainWindow.dir\MainWindow.cpp.i

src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainWindow.dir/MainWindow.cpp.s"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\savmo\Documents\Client\src\MainWindow\MainWindow.cpp -o CMakeFiles\MainWindow.dir\MainWindow.cpp.s

# Object files for target MainWindow
MainWindow_OBJECTS = \
"CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/MainWindow.dir/MainWindow.cpp.obj"

# External object files for target MainWindow
MainWindow_EXTERNAL_OBJECTS =

src/MainWindow/libMainWindow.a: src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow_autogen/mocs_compilation.cpp.obj
src/MainWindow/libMainWindow.a: src/MainWindow/CMakeFiles/MainWindow.dir/MainWindow.cpp.obj
src/MainWindow/libMainWindow.a: src/MainWindow/CMakeFiles/MainWindow.dir/build.make
src/MainWindow/libMainWindow.a: src/MainWindow/CMakeFiles/MainWindow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libMainWindow.a"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && $(CMAKE_COMMAND) -P CMakeFiles\MainWindow.dir\cmake_clean_target.cmake
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MainWindow.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/MainWindow/CMakeFiles/MainWindow.dir/build: src/MainWindow/libMainWindow.a

.PHONY : src/MainWindow/CMakeFiles/MainWindow.dir/build

src/MainWindow/CMakeFiles/MainWindow.dir/clean:
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow && $(CMAKE_COMMAND) -P CMakeFiles\MainWindow.dir\cmake_clean.cmake
.PHONY : src/MainWindow/CMakeFiles/MainWindow.dir/clean

src/MainWindow/CMakeFiles/MainWindow.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\savmo\Documents\Client C:\Users\savmo\Documents\Client\src\MainWindow C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\MainWindow\CMakeFiles\MainWindow.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/MainWindow/CMakeFiles/MainWindow.dir/depend

