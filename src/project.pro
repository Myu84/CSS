QT += core gui widgets printsupport

TARGET = cs3307-orange
TEMPLATE = app
CONFIG += c++11
win32 {
	CONFIG += windows
}
CONFIG(release, debug|release) {
	DEFINES += "QT_NO_DEBUG_OUTPUT"
}

SOURCES += main.cpp \
    parser/PresentationParser.cpp ui/PresentationDashboardWindow.cpp \
    parser/TeachingParser.cpp ui/TeachingDashboardWindow.cpp \
    parser/GrantParser.cpp ui/GrantDashboardWindow.cpp \
    parser/PublicationParser.cpp ui/PublicationDashboardWindow.cpp \
    ui/DashboardWindow.cpp ui/VisualizationWindow.cpp ui/FileInputDialog.cpp \
    ../external/qcustomplot.cpp \
    ui/PieChartWidget.cpp

FORMS += ui/DashboardWindow.ui ui/VisualizationWindow.ui ui/FileInputDialog.ui

HEADERS += \
    records/PresentationRecord.h parser/PresentationParser.h ui/PresentationDashboardWindow.h \
    records/TeachingRecord.h parser/TeachingParser.h ui/TeachingDashboardWindow.h \
    records/GrantRecord.h parser/GrantParser.h ui/GrantDashboardWindow.h \
    records/PublicationRecord.h parser/PublicationParser.h ui/PublicationDashboardWindow.h \
    parser/Parser.h \
    ui/DashboardWindow.h ui/VisualizationWindow.h ui/FileInputDialog.h \
	ui/UIUtils.h \
    ../external/qcustomplot.h ../external/csv.h \
    ui/PieChartWidget.h
