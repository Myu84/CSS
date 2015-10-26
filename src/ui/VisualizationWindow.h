#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include <QDialog>
#include <QList>

#include "ui_VisualizationWindow.h"
#include "../records/PresentationRecord.h"

class VisualizationWindow : public QDialog {
	Q_OBJECT

public:
	explicit VisualizationWindow(QWidget *parent = nullptr);
    void init(const QList<PresentationRecord> &records, QString &memberName, QDate &startDate, QDate &endDate);

private:
	Ui::VisualizationWindow ui;
};

#endif
