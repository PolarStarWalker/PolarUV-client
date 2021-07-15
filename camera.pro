QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvtest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += D:\lib\OpenCV\build\install\include
DEPENDPATH += D:\lib\OpenCV\build\install\include


LIBS +=-LD:\lib\OpenCV\build\install\x64\mingw\lib

LIBS += -lopencv_videoio451
LIBS += -lopencv_core451
LIBS += -lopencv_video451
LIBS += -lopencv_highgui451
LIBS += -lopencv_features2d451
LIBS += -lopencv_calib3d451

# more correct variant, how set includepath and libs for mingw
# add system variable: OPENCV_SDK_DIR=D:/opencv/opencv-build/install
# read http://doc.qt.io/qt-5/qmake-variable-reference.html#libs

#INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

#LIBS += -L$$(OPENCV_SDK_DIR)\x64\mingw\bin \
#        -lopencv_core415        \
#        -lopencv_highgui415     \
#        -lopencv_imgcodecs415   \
#        -lopencv_imgproc415     \
#        -lopencv_features2d415  \
#        -lopencv_calib3d415
