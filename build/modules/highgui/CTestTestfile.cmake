# CMake generated Testfile for 
# Source directory: D:/lib/OpenCV/src/modules/highgui
# Build directory: D:/lib/OpenCV/build/modules/highgui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_highgui "D:/lib/OpenCV/build/bin/opencv_test_highgui.exe" "--gtest_output=xml:opencv_test_highgui.xml")
set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;D:/lib/OpenCV/src/modules/highgui/CMakeLists.txt;165;ocv_add_accuracy_tests;D:/lib/OpenCV/src/modules/highgui/CMakeLists.txt;0;")
