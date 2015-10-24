#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>

#include "ui_DashboardWindow.h"

class DashboardWindow : public QMainWindow {
    Q_OBJECT

 public:
	static DashboardWindow *makeDashboard();
	
 protected:
    DashboardWindow();
    Ui::DashboardWindow ui;
};

#endif
