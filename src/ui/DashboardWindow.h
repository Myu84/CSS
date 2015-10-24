#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QDialog>

#include "ui_DashboardWindow.h"

class DashboardWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit DashboardWindow();

private:
    Ui::DashboardWindow ui;
};

#endif
