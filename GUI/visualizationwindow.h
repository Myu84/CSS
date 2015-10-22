#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include <QDialog>

namespace Ui {
class VisualizationWindow;
}

class VisualizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VisualizationWindow(QWidget *parent = 0);
    ~VisualizationWindow();

private:
    Ui::VisualizationWindow *ui;
};

#endif // VISUALIZATIONWINDOW_H
