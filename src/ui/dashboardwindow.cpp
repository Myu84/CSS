#include "dashboardwindow.h"
#include "ui_dashboardwindow.h"

DashboardWindow::DashboardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DashboardWindow)
{
    ui->setupUi(this);
}

DashboardWindow::~DashboardWindow()
{
    delete ui;
}
