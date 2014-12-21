#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T12:27:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CubeFromBlender
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    Cube.cpp \
    Scene.cpp \
    ObjLoader.cpp

HEADERS  += Dialog.h \
    Cube.h \
    Scene.h \
    ObjLoader.h

FORMS    += Dialog.ui

RESOURCES += \
    Shaders.qrc
