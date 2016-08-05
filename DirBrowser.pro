#-------------------------------------------------
#
# Project created by QtCreator 2016-07-31T23:07:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DirBrowser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    browser.cpp \
    worker.cpp \
    system.cpp

HEADERS  += mainwindow.h \
    browser.h \
    worker.h \
    system.h

FORMS    += mainwindow.ui
