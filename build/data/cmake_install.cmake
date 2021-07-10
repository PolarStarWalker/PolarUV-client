# Install script for directory: D:/lib/OpenCV/src/data

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/lib/OpenCV/build/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Qt/Tools/mingw810_64/bin/objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/haarcascades" TYPE FILE FILES
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_eye.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_frontalcatface.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_frontalcatface_extended.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_frontalface_alt.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_frontalface_alt2.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_frontalface_alt_tree.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_frontalface_default.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_fullbody.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_lefteye_2splits.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_licence_plate_rus_16stages.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_lowerbody.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_profileface.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_righteye_2splits.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_russian_plate_number.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_smile.xml"
    "D:/lib/OpenCV/src/data/haarcascades/haarcascade_upperbody.xml"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/lbpcascades" TYPE FILE FILES
    "D:/lib/OpenCV/src/data/lbpcascades/lbpcascade_frontalcatface.xml"
    "D:/lib/OpenCV/src/data/lbpcascades/lbpcascade_frontalface.xml"
    "D:/lib/OpenCV/src/data/lbpcascades/lbpcascade_frontalface_improved.xml"
    "D:/lib/OpenCV/src/data/lbpcascades/lbpcascade_profileface.xml"
    "D:/lib/OpenCV/src/data/lbpcascades/lbpcascade_silverware.xml"
    )
endif()

