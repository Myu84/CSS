#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include <QDialog>

#include "ui_VisualizationWindow.h"

class VisualizationWindow : public QDialog {
	Q_OBJECT

public:
	explicit VisualizationWindow(QWidget *parent = nullptr);

private:
	Ui::VisualizationWindow ui;
};

#endif
