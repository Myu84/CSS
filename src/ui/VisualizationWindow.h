#ifndef VISUALIZATIONWINDOW_H
#define VISUALIZATIONWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include <QString>
#include <QPaintEvent>
#include <QColor>

#include "ui_VisualizationWindow.h"
#include "../records/PresentationRecord.h"
#include "../external/qcustomplot.h"
#include "../external/nightchart/nightchartswidget.h"

class VisualizationWindow : public QMainWindow {
	Q_OBJECT

public:
    VisualizationWindow(const QList<QMap<QString, double>> &plotData, const QList<QString> &plotNames,
						const QString &memberName, const QDate &startDate, const QDate &endDate);

    ~VisualizationWindow() {
        graphs->clearItems();
        delete graphs;
        delete pieChart;
    }

private slots:
    void on_plotButton_clicked();
    void on_actionPrint_triggered();
    void on_actionExport_triggered();
    void on_actionClose_triggered();

private:
	void drawBarGraph(const QMap<QString, double> &plotData);
    void drawScatterPlot(const QMap<QString, double> &plotData);
    void drawPieGraph(const QMap<QString, double> &plotData);
    // clears all bars/graphs from the visualization
    void clearVis();
    // format the graph
    void styleGraph(QVector<double> &values, QVector<double> &ticks, QVector<QString> &keys);
	
	Ui::VisualizationWindow ui;
	
	QList<QMap<QString, double>> allPlotData;
    NightchartsWidget *pieChart;
    QCustomPlot *graphs;
    QList<QColor> colorList;
};

#endif
