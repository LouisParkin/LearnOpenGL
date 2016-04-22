#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T09:41:19
#
#-------------------------------------------------

QT       += core gui opengl concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LearnOpenGL
TEMPLATE = app

INCLUDEPATH += ../../Source \
               ../../Include \
               ../../Include/assimp

SOURCES += ../../Source/main.cpp\
           ../../Source/mainwindow.cpp \
           ../../Source/GLWidget.cpp \
           ../../Common/ogldev_util.cpp

HEADERS  += ../../Source/mainwindow.h \
            ../../Source/GLWidget.h

FORMS    += ../../Source/mainwindow.ui

LIBS += -lglut -lGLEW -Lassimp
