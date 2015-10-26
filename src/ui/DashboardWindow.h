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
    void on_backButton_clicked();
	
 protected slots:
    virtual void on_treeWidget_doubleClicked() = 0;

 protected:
    DashboardWindow();
	void updateDateLabel();
	virtual void updateTreeWidget() = 0;
	
    Ui::DashboardWindow ui;
};

#endif
