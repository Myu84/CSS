#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>

#include "ui_DashboardWindow.h"

class DashboardWindow : public QMainWindow {
    Q_OBJECT

 public:
	static DashboardWindow *makeDashboard();

 private slots:
	void on_actionExit_triggered();
	void on_dateFilterButton_clicked();
	
 protected:
    DashboardWindow();
	void updateDateLabel();
	virtual void updateTreeWidget() = 0;
	
    Ui::DashboardWindow ui;
};

#endif
