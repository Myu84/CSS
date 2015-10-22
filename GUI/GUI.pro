QT += core
QT -= gui

TARGET = GUI
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    fileinputdialog.cpp \
    dashboardwindow.cpp \
    visualizationwindow.cpp \
    qcustomplot/qcustomplot.cpp \
    errorlistdialog.cpp

FORMS += \
    fileinputdialog.ui \
    dashboardwindow.ui \
    visualizationwindow.ui \
    errorlistdialog.ui

HEADERS += \
    fileinputdialog.h \
    dashboardwindow.h \
    visualizationwindow.h \
    qcustomplot/qcustomplot.h \
    errorlistdialog.h

