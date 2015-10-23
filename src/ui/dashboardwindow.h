#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QDialog>

namespace Ui {
class DashboardWindow;
}

class DashboardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = 0);
    ~DashboardWindow();

private:
    Ui::DashboardWindow *ui;
};

#endif // DASHBOARDWINDOW_H
