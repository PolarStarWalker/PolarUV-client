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
include src/CMakeFiles/Client.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Client.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Client.dir/flags.make

src/CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.obj: src/CMakeFiles/Client.dir/flags.make
src/CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.obj: src/CMakeFiles/Client.dir/includes_CXX.rsp
src/CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.obj: src/Client_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.obj"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:/Users/savmo/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/211.7442.42/bin/cmake/win/bin/cmake.exe -E time C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.obj -c C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\Client_autogen\mocs_compilation.cpp

src/CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.i"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\Client_autogen\mocs_compilation.cpp > CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.i

src/CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.s"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\Client_autogen\mocs_compilation.cpp -o CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.s

src/CMakeFiles/Client.dir/main.cpp.obj: src/CMakeFiles/Client.dir/flags.make
src/CMakeFiles/Client.dir/main.cpp.obj: src/CMakeFiles/Client.dir/includes_CXX.rsp
src/CMakeFiles/Client.dir/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/Client.dir/main.cpp.obj"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:/Users/savmo/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/211.7442.42/bin/cmake/win/bin/cmake.exe -E time C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Client.dir\main.cpp.obj -c C:\Users\savmo\Documents\Client\src\main.cpp

src/CMakeFiles/Client.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/main.cpp.i"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\savmo\Documents\Client\src\main.cpp > CMakeFiles\Client.dir\main.cpp.i

src/CMakeFiles/Client.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/main.cpp.s"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Qt\Tools\mingw810_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\savmo\Documents\Client\src\main.cpp -o CMakeFiles\Client.dir\main.cpp.s

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/Client.dir/main.cpp.obj"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

src/Client.exe: src/CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.obj
src/Client.exe: src/CMakeFiles/Client.dir/main.cpp.obj
src/Client.exe: src/CMakeFiles/Client.dir/build.make
src/Client.exe: src/DataProtocol/libDataProtocol.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_gapi451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_highgui451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_ml451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_objdetect451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_photo451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_stitching451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_video451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_videoio451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_dnn451.dll.a
src/Client.exe: C:/Qt/5.15.2/mingw81_64/lib/libQt5Widgets.a
src/Client.exe: C:/Qt/5.15.2/mingw81_64/lib/libQt5Gui.a
src/Client.exe: C:/Qt/5.15.2/mingw81_64/lib/libQt5Test.a
src/Client.exe: C:/Qt/5.15.2/mingw81_64/lib/libQt5Core.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_imgcodecs451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_calib3d451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_features2d451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_flann451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_imgproc451.dll.a
src/Client.exe: D:/lib/OpenCV/build/lib/libopencv_core451.dll.a
src/Client.exe: src/CMakeFiles/Client.dir/linklibs.rsp
src/Client.exe: src/CMakeFiles/Client.dir/objects1.rsp
src/Client.exe: src/CMakeFiles/Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Client.exe"
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Client.dir\link.txt --verbose=$(VERBOSE)
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E make_directory C:/Users/savmo/Documents/Client/cmake-build-release-qtcmake/src/plugins/platforms/
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E copy C:/Qt/5.15.2/mingw81_64/lib/cmake/../../plugins/platforms/qwindows.dll C:/Users/savmo/Documents/Client/cmake-build-release-qtcmake/src/plugins/platforms/
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E copy C:/Qt/5.15.2/mingw81_64/lib/cmake/../../bin/Qt5Core.dll C:/Users/savmo/Documents/Client/cmake-build-release-qtcmake/src
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E copy C:/Qt/5.15.2/mingw81_64/lib/cmake/../../bin/Qt5Gui.dll C:/Users/savmo/Documents/Client/cmake-build-release-qtcmake/src
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E copy C:/Qt/5.15.2/mingw81_64/lib/cmake/../../bin/Qt5Widgets.dll C:/Users/savmo/Documents/Client/cmake-build-release-qtcmake/src
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && C:\Users\savmo\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E copy C:/Qt/5.15.2/mingw81_64/lib/cmake/../../bin/Qt5Test.dll C:/Users/savmo/Documents/Client/cmake-build-release-qtcmake/src

# Rule to build all files generated by this target.
src/CMakeFiles/Client.dir/build: src/Client.exe

.PHONY : src/CMakeFiles/Client.dir/build

src/CMakeFiles/Client.dir/clean:
	cd /d C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src && $(CMAKE_COMMAND) -P CMakeFiles\Client.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/Client.dir/clean

src/CMakeFiles/Client.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\savmo\Documents\Client C:\Users\savmo\Documents\Client\src C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src C:\Users\savmo\Documents\Client\cmake-build-release-qtcmake\src\CMakeFiles\Client.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Client.dir/depend

