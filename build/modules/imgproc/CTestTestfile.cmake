# CMake generated Testfile for 
# Source directory: D:/lib/OpenCV/src/modules/imgproc
# Build directory: D:/lib/OpenCV/build/modules/imgproc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_imgproc "D:/lib/OpenCV/build/bin/opencv_test_imgproc.exe" "--gtest_output=xml:opencv_test_imgproc.xml")
set_tests_properties(opencv_test_imgproc PROPERTIES  LABELS "Main;opencv_imgproc;Accuracy" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1311;ocv_add_test_from_target;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1075;ocv_add_accuracy_tests;D:/lib/OpenCV/src/modules/imgproc/CMakeLists.txt;13;ocv_define_module;D:/lib/OpenCV/src/modules/imgproc/CMakeLists.txt;0;")
add_test(opencv_perf_imgproc "D:/lib/OpenCV/build/bin/opencv_perf_imgproc.exe" "--gtest_output=xml:opencv_perf_imgproc.xml")
set_tests_properties(opencv_perf_imgproc PROPERTIES  LABELS "Main;opencv_imgproc;Performance" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/performance" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1213;ocv_add_test_from_target;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1076;ocv_add_perf_tests;D:/lib/OpenCV/src/modules/imgproc/CMakeLists.txt;13;ocv_define_module;D:/lib/OpenCV/src/modules/imgproc/CMakeLists.txt;0;")
add_test(opencv_sanity_imgproc "D:/lib/OpenCV/build/bin/opencv_perf_imgproc.exe" "--gtest_output=xml:opencv_perf_imgproc.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_imgproc PROPERTIES  LABELS "Main;opencv_imgproc;Sanity" WORKING_DIRECTORY "D:/lib/OpenCV/build/test-reports/sanity" _BACKTRACE_TRIPLES "D:/lib/OpenCV/src/cmake/OpenCVUtils.cmake;1677;add_test;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1214;ocv_add_test_from_target;D:/lib/OpenCV/src/cmake/OpenCVModule.cmake;1076;ocv_add_perf_tests;D:/lib/OpenCV/src/modules/imgproc/CMakeLists.txt;13;ocv_define_module;D:/lib/OpenCV/src/modules/imgproc/CMakeLists.txt;0;")
