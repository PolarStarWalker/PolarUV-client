# CMake generated Testfile for 
# Source directory: D:/lib/OpenCV/src/modules/flann
# Build directory: D:/lib/OpenCV/build/modules/flann
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_flann "D:/lib/OpenCV/build/bin/opencv_test_flann.exe" "--gtest_output=xml:opencv_test_flann.xml")
set_tests_properties(opencv_test_flann PROPERTIES  LABELS "Main;opencv_flann;Accuracy" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1075;ocv_add_accuracy_tests;D:/lib/OpenCV/src/modules/flann/CMakeLists.txt;2;ocv_define_module;D:/lib/OpenCV/src/modules/flann/CMakeLists.txt;0;")
