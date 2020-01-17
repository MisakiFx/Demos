#-------------------------------------------------
#
# Project created by QtCreator 2020-01-18T01:34:21
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimplePlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    playerrs.qrc
CONFIG += C++11
