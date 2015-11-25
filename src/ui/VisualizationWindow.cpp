#include <QList>
#include <QMap>
#include <QString>
#include <QStringRef>
#include <QDate>
#include <QPen>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

#include <math.h>

#include "VisualizationWindow.h"
#include "ui_VisualizationWindow.h"
#include "../../external/qcustomplot.h"
#include "UIUtils.h"
#include "PieChartWidget.h"

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
 : allPlotData(plotData) {
	ui.setupUi(this);
	
	ui.memberNameLabel->setText("Visualization for " + memberName);
    ui.dateRangeLabel->setText("Showing records from " + 
							   startDate.toString("MMM d yyyy") + 
							   " to " + 
							   endDate.toString("MMM d yyyy"));
	ui.plotDataSelect->addItems(plotNames);

    setWindowTitle("Visualizations - " + memberName);

    /* x axis */
    ui.visualization->xAxis->setAutoTicks(false);
    ui.visualization->xAxis->setAutoTickLabels(false);
    ui.visualization->xAxis->setTickLabelRotation(60);
    ui.visualization->xAxis->setTickLength(0, 4);
    ui.visualization->xAxis->grid()->setVisible(true);
    ui.visualization->xAxis->setSubTickCount(0);

    /* y axis */
    // these four methods force the y-axis to increment integers only
    ui.visualization->yAxis->setAutoTickStep(false);
    ui.visualization->yAxis->setAutoSubTicks(false);
    ui.visualization->yAxis->setSubTickCount(0);
	
	on_plotButton_clicked();
}

void VisualizationWindow::on_actionClose_triggered() {
	close();
}

void VisualizationWindow::on_plotButton_clicked() {
	int plotDataIndex = ui.plotDataSelect->currentIndex();
	QString plotType = ui.plotTypeSelect->currentText();

    clearVis();

	if (plotType == "Bar Graph") {
		drawBarGraph(allPlotData[plotDataIndex]);
        ui.visualization->raise();
        //ui.vis2->setVisible(false);
	} else if (plotType == "Scatter Plot") {
		drawScatterPlot(allPlotData[plotDataIndex]);
        ui.visualization->raise();
        //ui.vis2->setVisible(false);
    } else if (plotType == "Pie Graph") {
        //ui.vis2->setVisible(true);
        ui.vis2->raise();
        drawPieGraph(allPlotData[plotDataIndex]);
    }

    ui.visualization->replot();
}

void VisualizationWindow::drawScatterPlot(const QMap<QString, double> &plotData) {
    QVector<QString> currKeys = plotData.keys().toVector();
    QVector<double> ticks = rangeVector(currKeys.size());
    QVector<double> currValues = plotData.values().toVector();

    ui.visualization->addGraph();
    ui.visualization->graph(0)->setData(ticks, currValues);
    ui.visualization->graph(0)->setLineStyle(QCPGraph::lsNone);

    /* Scatter style */
    QCPScatterStyle scatterStyle;
    scatterStyle.setShape(QCPScatterStyle::ssCircle);
    scatterStyle.setPen(QPen(Qt::blue));
    scatterStyle.setBrush(Qt::white);
    scatterStyle.setSize(5);
    ui.visualization->graph(0)->setScatterStyle(scatterStyle);

    styleGraph(currValues, ticks, currKeys);
}

void VisualizationWindow::drawPieGraph(const QMap<QString, double> &plotData)
{
    QVector<QString> currKeys = plotData.keys().toVector();
    QVector<double> currValues = plotData.values().toVector();

    ui.vis2->setData(currKeys, currValues);
    ui.vis2->resize(ui.visualization->width(), ui.visualization->height());
}

void VisualizationWindow::drawBarGraph(const QMap<QString, double> &plotData) {
	QVector<QString> currKeys = plotData.keys().toVector();
	QVector<double> ticks = rangeVector(currKeys.size());
	QVector<double> currValues = plotData.values().toVector();

    QCPBars *barGraph = new QCPBars(ui.visualization->xAxis, ui.visualization->yAxis);
    ui.visualization->addPlottable(barGraph);
	
    // bar outline thickness
    QPen pen;
    pen.setWidthF(1.2);
    barGraph->setPen(pen);

    styleGraph(currValues, ticks, currKeys);

    barGraph->setData(ticks, currValues);
}

void VisualizationWindow::clearVis() {
    ui.visualization->clearPlottables();
    ui.visualization->clearGraphs();
}

void VisualizationWindow::styleGraph(QVector<double> &values, QVector<double> &ticks, QVector<QString> &keys)
{
    ui.visualization->xAxis->setTickVector(ticks);
    ui.visualization->xAxis->setTickVectorLabels(keys);
    ui.visualization->xAxis->setRange(0, keys.size() + 1);

    /* y axis */
    double valueMax = vectorMax(values);
    double yMax = valueMax + ceil(valueMax*0.01);

    ui.visualization->yAxis->setRange(0, yMax);

    // set number of ticks on y-axis to a reasonable amount
    double tickstep = ceil(yMax/10);
    ui.visualization->yAxis->setTickStep(tickstep);
}

void VisualizationWindow::on_actionExport_triggered() {
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Graph"));

    if (dialog->exec() != QDialog::Accepted)
        return;

    // actual printing starts here
    QPainter painter;
    painter.setRenderHints(QPainter::Antialiasing);
    painter.begin(&printer);
    ui.visualization->render(&painter);
}
