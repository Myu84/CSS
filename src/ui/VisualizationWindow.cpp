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
#include <QSizePolicy>

#include <math.h>

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
 : allPlotData(plotData) {
	ui.setupUi(this);
	
	ui.memberNameLabel->setText("Visualization for " + memberName);
    ui.dateRangeLabel->setText("Showing records from " + 
							   startDate.toString("MMM d yyyy") + 
							   " to " + 
							   endDate.toString("MMM d yyyy"));
	ui.plotDataSelect->addItems(plotNames);

    setWindowTitle("Visualizations - " + memberName);

    QGridLayout* layout = new QGridLayout(ui.visWidget);

    graphs = new QCustomPlot();
    pieChart = new PieChartWidget();

    //ui.visWidget->setLayout(layout);
    graphs->setAccessibleName("graphs");
    pieChart->setAccessibleName("pieChart");

    graphs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pieChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(graphs, 0, 0);
    layout->addWidget(pieChart, 0 , 0);

    graphs->xAxis->setAutoTicks(false);
    graphs->xAxis->setAutoTickLabels(false);
    graphs->xAxis->setTickLabelRotation(60);
    graphs->xAxis->setTickLength(0, 4);
    graphs->xAxis->grid()->setVisible(true);
    graphs->xAxis->setSubTickCount(0);

    graphs->yAxis->setAutoTickStep(false);
    graphs->yAxis->setAutoSubTicks(false);
    graphs->yAxis->setSubTickCount(0);

    //ui.visWidget->setLayout(layout);

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
        graphs->raise();
        //ui.vis2->setVisible(false);
	} else if (plotType == "Scatter Plot") {
		drawScatterPlot(allPlotData[plotDataIndex]);
        graphs->raise();
        //ui.vis2->setVisible(false);
    } else if (plotType == "Pie Graph") {
        //ui.vis2->setVisible(true);
        pieChart->raise();
        drawPieGraph(allPlotData[plotDataIndex]);
    }

    graphs->replot();
}

void VisualizationWindow::drawScatterPlot(const QMap<QString, double> &plotData) {
    QVector<QString> currKeys = plotData.keys().toVector();
    QVector<double> ticks = rangeVector(currKeys.size());
    QVector<double> currValues = plotData.values().toVector();

    graphs->addGraph();
    graphs->graph(0)->setData(ticks, currValues);
    graphs->graph(0)->setLineStyle(QCPGraph::lsNone);

    /* Scatter style */
    QCPScatterStyle scatterStyle;
    scatterStyle.setShape(QCPScatterStyle::ssCircle);
    scatterStyle.setPen(QPen(Qt::blue));
    scatterStyle.setBrush(Qt::white);
    scatterStyle.setSize(5);
    graphs->graph(0)->setScatterStyle(scatterStyle);

    styleGraph(currValues, ticks, currKeys);
}

void VisualizationWindow::drawPieGraph(const QMap<QString, double> &plotData)
{
    QVector<QString> currKeys = plotData.keys().toVector();
    QVector<double> currValues = plotData.values().toVector();

    pieChart->setData(currKeys, currValues);
    pieChart->resize(ui.visWidget->width(), ui.visWidget->height());
}

void VisualizationWindow::drawBarGraph(const QMap<QString, double> &plotData) {
	QVector<QString> currKeys = plotData.keys().toVector();
	QVector<double> ticks = rangeVector(currKeys.size());
	QVector<double> currValues = plotData.values().toVector();

    QCPBars *barGraph = new QCPBars(graphs->xAxis, graphs->yAxis);
    graphs->addPlottable(barGraph);
	
    // bar outline thickness
    QPen pen;
    pen.setWidthF(1.2);
    barGraph->setPen(pen);

    styleGraph(currValues, ticks, currKeys);

    barGraph->setData(ticks, currValues);
}

void VisualizationWindow::clearVis() {
    graphs->clearPlottables();
    graphs->clearGraphs();
}

void VisualizationWindow::styleGraph(QVector<double> &values, QVector<double> &ticks, QVector<QString> &keys)
{
    graphs->xAxis->setTickVector(ticks);
    graphs->xAxis->setTickVectorLabels(keys);
    graphs->xAxis->setRange(0, keys.size() + 1);

    /* y axis */
    double valueMax = vectorMax(values);
    double yMax = valueMax + ceil(valueMax*0.01);

    graphs->yAxis->setRange(0, yMax);

    // set number of ticks on y-axis to a reasonable amount
    double tickstep = ceil(yMax/10);
    graphs->yAxis->setTickStep(tickstep);
}

void VisualizationWindow::on_actionExport_triggered() {
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Graph"));

    if (dialog->exec() != QDialog::Accepted)
        return;

    // actual printing starts here
    QPainter painter;
    painter.setRenderHints(QPainter::Antialiasing);
    painter.begin(&printer);
    graphs->render(&painter);
}
