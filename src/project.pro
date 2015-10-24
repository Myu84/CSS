QT += core gui widgets printsupport

TARGET = cs3307-orange
TEMPLATE = app
CONFIG += c++11
win32 {
	CONFIG += windows
}

SOURCES += main.cpp \
    parser/PresentationParser.cpp \
    ui/dashboardwindow.cpp ui/visualizationwindow.cpp ui/errorlistdialog.cpp ui/FileInputDialog.cpp \
    ../external/qcustomplot.cpp

FORMS += ui/FileInputDialog.ui ui/dashboardwindow.ui ui/visualizationwindow.ui ui/errorlistdialog.ui

HEADERS += \
    parser/Parser.h parser/PresentationParser.h \
    ui/dashboardwindow.h ui/visualizationwindow.h ui/errorlistdialog.h ui/FileInputDialog.h \
    ../external/qcustomplot.h ../external/csv.h
