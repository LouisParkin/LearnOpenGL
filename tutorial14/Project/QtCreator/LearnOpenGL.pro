#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T09:41:19
#
#-------------------------------------------------

QT       += core gui opengl concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LearnOpenGL
TEMPLATE = app

INCLUDEPATH += $$PWD/../../Source \
               $$PWD/../../Include \
               $$PWD/../../Include/assimp \
               $$PWD/../../Include/ATB

INCLUDEPATH += $$PWD/../../Lib

DEPENDPATH += $$PWD/../../Lib

SOURCES += $$PWD/../../Source/main.cpp\
           $$PWD/../../Source/mainwindow.cpp \
           $$PWD/../../Source/GLWidget.cpp \
           $$PWD/../../Common/ogldev_util.cpp \
           $$PWD/../../Common/math_3d.cpp \
           $$PWD/../../Common/pipeline.cpp \
           $$PWD/../../Common/camera.cpp \
           $$PWD/../../Common/ogldev_atb.cpp \
           $$PWD/../../Common/ogldev_backend.cpp \
           $$PWD/../../Common/glut_backend.cpp \
           $$PWD/../../Common/ogldev_glfw_backend.cpp

HEADERS  += $$PWD/../../Source/mainwindow.h \
            $$PWD/../../Source/GLWidget.h

FORMS    += $$PWD/../../Source/mainwindow.ui

LIBS += -L/home/lparkin/Projects/S3/LearnOpenGL/Lib

LIBS += -lglut -lGLEW -lAntTweakBar -lglfw

#-lassimp

