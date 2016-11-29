#-------------------------------------------------
#
# Project created by QtCreator 2016-11-28T16:21:51
#
#-------------------------------------------------

QT       += core gui

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = id_swap_faces
TEMPLATE = app

LIBS += -lX11 -lpthread

SOURCES += main.cpp\
        mainwindow.cpp \
    face_detection.cpp \
    face_recognition.cpp \
    face_swap.cpp

HEADERS  += mainwindow.h \
    face_detection.h \
    face_recognition.h \
    face_swap.h \
    CImg.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
