QT += core
QT -= gui

TARGET = GUI
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    fileinputdialog.cpp \
    dashboardwindow.cpp

FORMS += \
    fileinputdialog.ui \
    dashboardwindow.ui

HEADERS += \
    fileinputdialog.h \
    dashboardwindow.h

