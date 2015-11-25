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

double vectorSum(QVector<double> vect) {
    double total = 0.0;
    for (double x: vect) {
        total+=x;
    }
    return total;
}

//QList<QColor> VisualizationWindow::colorList << Qt::red << Qt::blue << Qt::green << Qt::yellow << Qt::magenta << Qt::cyan << Qt::gray << Qt::darkRed << Qt::darkGreen << Qt::darkBlue;

VisualizationWindow::VisualizationWindow(const QList<QMap<QString, double>> &plotData, const QList<QString> &plotNames,
										 const QString &memberName, const QDate &startDate, const QDate &endDate)
 : allPlotData(plotData) {
	ui.setupUi(this);
	
    ui.visWidget->setStyleSheet("background-color:white;");
	ui.plotDataSelect->addItems(plotNames);

    setWindowTitle("Visualizations - " + memberName);

    QGridLayout* layout = new QGridLayout(ui.visWidget);

    graphs = new QCustomPlot(ui.visWidget);
    pieChart = new NightchartsWidget(ui.visWidget);
    graphs->raise();

    graphs->setAccessibleName("graphs");
    pieChart->setAccessibleName("pieChart");

    graphs->plotLayout()->insertRow(0);
    graphs->plotLayout()->addElement(0, 0, new QCPPlotTitle(graphs,
                                                            memberName + " - " + startDate.toString("MMM d yyyy") +
                                                            " to " + endDate.toString("MMM d yyyy")));

    layout->addWidget(graphs,0,0);
    layout->addWidget(pieChart,0,0);

    graphs->xAxis->setAutoTicks(false);
    graphs->xAxis->setAutoTickLabels(false);
    graphs->xAxis->setTickLabelRotation(60);
    graphs->xAxis->setTickLength(0, 4);
    graphs->xAxis->grid()->setVisible(true);
    graphs->xAxis->setSubTickCount(0);

    graphs->yAxis->setAutoTickStep(false);
    graphs->yAxis->setAutoSubTicks(false);
    graphs->yAxis->setSubTickCount(0);

    colorList << QColor("#8dd3c7") << QColor("#ffffb3") << QColor("#bebada") << QColor("#fb8072") << QColor("#80b1d3") << QColor("#fbd462");
    colorList << QColor("#b3de69") << QColor("#fccde5") << QColor("#d9d9d9") << QColor("#bc80bd") << QColor("#ccebc5") << QColor("#ffed6f");
    colorList << QColor("#1f78b4") << QColor("#33a02c") << QColor("#e31a1c") << QColor("#ff7f00") << QColor("#6a3d9a") << QColor("#a6cee3");

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
       // graphs->plotLayout()->addElement(0, 0, new QCPPlotTitle(graphs, "test title"));
        graphs->setVisible(true);
	} else if (plotType == "Scatter Plot") {
		drawScatterPlot(allPlotData[plotDataIndex]);
       // graphs->plotLayout()->addElement(0, 0, new QCPPlotTitle(graphs, "test title"));
        graphs->setVisible(true);
    } else if (plotType == "Pie Graph") {
        graphs->setVisible(false);
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

    int color = 0;
    double total = vectorSum(currValues);
    int cSize = colorList.size();

    pieChart->clear();
    pieChart->setType(Nightcharts::Pie);

    for (int i = 0; i < currKeys.size(); i++) {
        double value = currValues.at(i);

        double pSize = (value/total) * 100;

        pieChart->addItem(currKeys.at(i), colorList.at(color%cSize), pSize);
        color++;
    }
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

void VisualizationWindow::styleGraph(QVector<double> &values, QVector<double> &ticks, QVector<QString> &keys) {
    graphs->xAxis->setTickVector(ticks);
    graphs->xAxis->setTickVectorLabels(keys);
    graphs->xAxis->setRange(0, keys.size() + 1);

    /* y axis */
    double valueMax = vectorMax(values);
    double yMax = valueMax;

    // set number of ticks on y-axis to a reasonable amount
    double tickstep = ceil(yMax/10);
    graphs->yAxis->setTickStep(tickstep);
    graphs->yAxis->setRange(0, yMax+tickstep);
}

void VisualizationWindow::on_actionPrint_triggered() {
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Graph"));

    if (dialog->exec() != QDialog::Accepted)
        return;

    // actual printing starts here
    QPainter painter;
    painter.setRenderHints(QPainter::Antialiasing);
    painter.begin(&printer);

    if (graphs->isVisible()) {
        graphs->render(&painter);
    } else {
        pieChart->render(&painter);
    }
}

void VisualizationWindow::on_actionExport_triggered() {
    QString ext;
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Graph"), "", tr("PDF (*.pdf);;JPG (*.jpg);;PNG (*.png)"), &ext);

    std::string stdext = ext.toStdString();

    if (stdext == "PDF (*.pdf)") {
        graphs->savePdf(filename);
    }
    else if (stdext == "PNG (*.png)") {
        graphs->savePng(filename);
    }
    else if (stdext == "JPG (*.jpg)") {
        graphs->saveJpg(filename);
    }
}
