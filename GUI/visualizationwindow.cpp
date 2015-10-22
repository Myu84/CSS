#include "visualizationwindow.h"
#include "ui_visualizationwindow.h"

VisualizationWindow::VisualizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VisualizationWindow)
{
    ui->setupUi(this);
}

VisualizationWindow::~VisualizationWindow()
{
    delete ui;
}
