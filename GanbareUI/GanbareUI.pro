QT       += core gui opengl webenginewidgets websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GanbareUI
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv\
               ../headers/
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core

SOURCES += main.cpp\
        mainwindow.cpp \
    opencvcontroller.cpp \
    qtserver.cpp

HEADERS  += mainwindow.h \
    opencvcontroller.h \
    qtserver.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
