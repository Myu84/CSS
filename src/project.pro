QT += core gui widgets printsupport

TARGET = cs3307-orange
TEMPLATE = app
CONFIG += c++11
win32 {
	CONFIG += windows
}

SOURCES += main.cpp \
    parser/PresentationParser.cpp ui/PresentationDashboardWindow.cpp \
    parser/TeachingParser.cpp ui/TeachingDashboardWindow.cpp \
    parser/GrantParser.cpp ui/GrantDashboardWindow.cpp \
    ui/DashboardWindow.cpp ui/VisualizationWindow.cpp ui/FileInputDialog.cpp \
    ../external/qcustomplot.cpp

FORMS += ui/DashboardWindow.ui ui/VisualizationWindow.ui ui/FileInputDialog.ui

HEADERS += \
    parser/PresentationParser.h ui/PresentationDashboardWindow.h \
    parser/TeachingParser.h ui/TeachingDashboardWindow.h \
    parser/GrantParser.h ui/GrantDashboardWindow.h \
    parser/Parser.h \
    ui/DashboardWindow.h ui/VisualizationWindow.h ui/FileInputDialog.h \
	ui/UIUtils.h \
    ../external/qcustomplot.h ../external/csv.h
