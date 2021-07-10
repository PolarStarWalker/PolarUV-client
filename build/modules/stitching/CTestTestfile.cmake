# CMake generated Testfile for 
# Source directory: D:/lib/OpenCV/src/modules/stitching
# Build directory: D:/lib/OpenCV/build/modules/stitching
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_stitching "D:/lib/OpenCV/build/bin/opencv_test_stitching.exe" "--gtest_output=xml:opencv_test_stitching.xml")
set_tests_properties(opencv_test_stitching PROPERTIES  LABELS "Main;opencv_stitching;Accuracy" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1075;ocv_add_accuracy_tests;D:/lib/OpenCV/src/modules/stitching/CMakeLists.txt;11;ocv_define_module;D:/lib/OpenCV/src/modules/stitching/CMakeLists.txt;0;")
add_test(opencv_perf_stitching "D:/lib/OpenCV/build/bin/opencv_perf_stitching.exe" "--gtest_output=xml:opencv_perf_stitching.xml")
set_tests_properties(opencv_perf_stitching PROPERTIES  LABELS "Main;opencv_stitching;Performance" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/performance" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1213;ocv_add_test_from_target;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1076;ocv_add_perf_tests;D:/lib/OpenCV/src/modules/stitching/CMakeLists.txt;11;ocv_define_module;D:/lib/OpenCV/src/modules/stitching/CMakeLists.txt;0;")
add_test(opencv_sanity_stitching "D:/lib/OpenCV/build/bin/opencv_perf_stitching.exe" "--gtest_output=xml:opencv_perf_stitching.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_stitching PROPERTIES  LABELS "Main;opencv_stitching;Sanity" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/sanity" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1214;ocv_add_test_from_target;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1076;ocv_add_perf_tests;D:/lib/OpenCV/src/modules/stitching/CMakeLists.txt;11;ocv_define_module;D:/lib/OpenCV/src/modules/stitching/CMakeLists.txt;0;")
