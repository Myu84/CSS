#include <QList>
#include <QMap>
#include <QString>
#include <QStringRef>
#include <QDate>
#include <QPen>
#include <QMessageBox>

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
	
	on_plotButton_clicked();
}

void VisualizationWindow::on_actionClose_triggered() {
	close();
}

void VisualizationWindow::on_plotButton_clicked() {
	int plotDataIndex = ui.plotDataSelect->currentIndex();
	QString plotType = ui.plotTypeSelect->currentText();
	
	if (plotType == "Bar Graph") {
		drawBarGraph(allPlotData[plotDataIndex]);
	} else if (plotType == "Scatter Plot") {
		drawScatterPlot(allPlotData[plotDataIndex]);
	}
}

void VisualizationWindow::drawScatterPlot(const QMap<QString, double> &plotData) {
    clearVis();

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

    /* x axis */
    ui.visualization->xAxis->setAutoTicks(false);
    ui.visualization->xAxis->setAutoTickLabels(false);
    ui.visualization->xAxis->setTickVector(ticks);
    ui.visualization->xAxis->setTickVectorLabels(currKeys);
    ui.visualization->xAxis->setTickLabelRotation(60);
    ui.visualization->xAxis->setTickLength(0, 4);
    ui.visualization->xAxis->grid()->setVisible(true);
    ui.visualization->xAxis->setSubTickCount(0);
    ui.visualization->xAxis->setRange(0, currKeys.size() + 1);

    /* y axis */
    // these four methods force the y-axis to increment integers only
    ui.visualization->yAxis->setAutoTickStep(false);
    ui.visualization->yAxis->setAutoSubTicks(false);
    ui.visualization->yAxis->setSubTickCount(0);
    ui.visualization->yAxis->setRange(0, vectorMax(currValues) + 0.1);
    ui.visualization->yAxis->setTickStep(1);
	
	ui.visualization->replot();
}

void VisualizationWindow::drawBarGraph(const QMap<QString, double> &plotData) {
    clearVis();
	
	QVector<QString> currKeys = plotData.keys().toVector();
	QVector<double> ticks = rangeVector(currKeys.size());
	QVector<double> currValues = plotData.values().toVector();
	
    QCPBars *barGraph = new QCPBars(ui.visualization->xAxis, ui.visualization->yAxis);
    ui.visualization->addPlottable(barGraph);
	
    // bar outline thickness
    QPen pen;
    pen.setWidthF(1.2);
    barGraph->setPen(pen);

    /* x axis */
    ui.visualization->xAxis->setAutoTicks(false);
    ui.visualization->xAxis->setAutoTickLabels(false);
    ui.visualization->xAxis->setTickVector(ticks);
    ui.visualization->xAxis->setTickVectorLabels(currKeys);
    ui.visualization->xAxis->setTickLabelRotation(60);
    ui.visualization->xAxis->setTickLength(0, 4);
    ui.visualization->xAxis->grid()->setVisible(true);
    ui.visualization->xAxis->setSubTickCount(0);
    ui.visualization->xAxis->setRange(0, currKeys.size() + 1);

    /* y axis */
    // these four methods force the y-axis to increment integers only
    ui.visualization->yAxis->setAutoTickStep(false);
    ui.visualization->yAxis->setAutoSubTicks(false);
    ui.visualization->yAxis->setSubTickCount(0);
    ui.visualization->yAxis->setRange(0, vectorMax(currValues) + 0.1);
    ui.visualization->yAxis->setTickStep(1);

    barGraph->setData(ticks, currValues);
	ui.visualization->replot();
}

void VisualizationWindow::clearVis() {
    ui.visualization->clearPlottables();
    ui.visualization->clearGraphs();
}

void VisualizationWindow::on_actionPrint_triggered() {
    QString ext;
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Graph"), "", tr("PDF (*.pdf);;JPG (*.jpg);;PNG (*.png)"), &ext);

    std::string stdext = ext.toStdString();

    if (stdext == "PDF (*.pdf)") {
        ui.visualization->savePdf(filename);
    }
    else if (stdext == "PNG (*.png)") {
        ui.visualization->savePng(filename);
    }
    else if (stdext == "JPG (*.jpg)") {
        ui.visualization->saveJpg(filename);
    } else {
        // show failure dialog
        QMessageBox::critical(this, "Error", "Could not save file.");
    }
}
