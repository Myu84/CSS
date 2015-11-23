#include <QList>
#include <QMap>
#include <QString>
#include <QDate>
#include <QPen>

#include "VisualizationWindow.h"
#include "ui_VisualizationWindow.h"
#include "../../external/qcustomplot.h"
#include "UIUtils.h"

QVector<double> rangeVector(int n) {
	QVector<double> output;
	for (int i = 1; i <= n; ++i) {
		output.append(i);
	}
	return output;
}

double vectorMax(QVector<double> vect) {
	double output = 0;
	for (double x : vect) {
		if (x > output) {
			output = x;
		}
	}
	return output;
}

VisualizationWindow::VisualizationWindow(const QList<QMap<QString, double>> &plotData, const QList<QString> &plotNames,
										 const QString &memberName, const QDate &startDate, const QDate &endDate)
 : plotData(plotData), plotNames(plotNames), memberName(memberName), startDate(startDate), endDate(endDate) {
	ui.setupUi(this);
	
	ui.GraphTitleLabel->setText("Visualization for " + memberName);
    ui.GraphTitleLabel->setAlignment(Qt::AlignHCenter);
    ui.DateRangeLabel->setText(startDate.toString("'From' MMMM d',' yyyy") +
                                endDate.toString("' to' MMMM d',' yyyy"));
    ui.DateRangeLabel->setAlignment(Qt::AlignHCenter);

    setWindowTitle("Visualizations - " + memberName);
	
	//just for now
	drawBarGraph();
}

void VisualizationWindow::drawBarGraph() {
    //just for now
	QMap<QString, double> currPlotData = plotData[0];
	QString currPlotName = plotNames[0];
	
	QVector<QString> currKeys = currPlotData.keys().toVector();
	QVector<double> ticks = rangeVector(currKeys.size());
	QVector<double> currValues = currPlotData.values().toVector();
	
    QCPBars *barGraph = new QCPBars(ui.Visualization->xAxis, ui.Visualization->yAxis);
	barGraph->setName(currPlotName);
    ui.Visualization->addPlottable(barGraph);
	
    // bar outline thickness
    QPen pen;
    pen.setWidthF(1.2);
    barGraph->setPen(pen);

    /* x axis */
    ui.Visualization->xAxis->setAutoTicks(false);
    ui.Visualization->xAxis->setAutoTickLabels(false);
    ui.Visualization->xAxis->setTickVector(ticks);
    ui.Visualization->xAxis->setTickVectorLabels(currKeys);
    ui.Visualization->xAxis->setTickLabelRotation(60);
    ui.Visualization->xAxis->setTickLength(0, 4);
    ui.Visualization->xAxis->grid()->setVisible(true);
    ui.Visualization->xAxis->setSubTickCount(0);
    ui.Visualization->xAxis->setRange(0, currKeys.size() + 1);

    /* y axis */
    // these four methods force the y-axis to increment integers only
    ui.Visualization->yAxis->setAutoTickStep(false);
    ui.Visualization->yAxis->setAutoSubTicks(false);
    ui.Visualization->yAxis->setSubTickCount(0);
    ui.Visualization->yAxis->setRange(0, vectorMax(currValues) + 0.1);
    ui.Visualization->yAxis->setTickStep(1);

    barGraph->setData(ticks, currValues);
}
