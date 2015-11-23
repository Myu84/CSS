#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include <QDialog>
#include <QList>

#include "ui_VisualizationWindow.h"
#include "../records/PresentationRecord.h"

class VisualizationWindow : public QDialog {
	Q_OBJECT

public:
	VisualizationWindow(const QList<QMap<QString, double>> &plotData, const QList<QString> &plotNames,
						const QString &memberName, const QDate &startDate, const QDate &endDate);

private:
	void drawBarGraph();
	
	Ui::VisualizationWindow ui;
	
	QList<QMap<QString, double>> plotData;
	QList<QString> plotNames;
	
	QString memberName;
	QDate startDate;
	QDate endDate;
};

#endif
