#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T09:41:19
#
#-------------------------------------------------

QT       += core gui opengl concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LearnOpenGL
TEMPLATE = app

INCLUDEPATH += ../../Louis/ogldev-source/Include \
               ../../Louis/ogldev-source/Include/assimp

SOURCES += main.cpp\
        mainwindow.cpp \
    GLWidget.cpp \
    ogldev_util.cpp

HEADERS  += mainwindow.h \
    GLWidget.h \
    math_3d.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLEW -Lassimp
