# CMake generated Testfile for 
# Source directory: D:/lib/OpenCV/src/modules/ml
# Build directory: D:/lib/OpenCV/build/modules/ml
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_ml "D:/lib/OpenCV/build/bin/opencv_test_ml.exe" "--gtest_output=xml:opencv_test_ml.xml")
set_tests_properties(opencv_test_ml PROPERTIES  LABELS "Main;opencv_ml;Accuracy" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1075;ocv_add_accuracy_tests;D:/lib/OpenCV/src/modules/ml/CMakeLists.txt;2;ocv_define_module;D:/lib/OpenCV/src/modules/ml/CMakeLists.txt;0;")
