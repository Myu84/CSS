#include <QSet>
#include <QVector>
#include <QPen>

#include "VisualizationWindow.h"
#include "ui_VisualizationWindow.h"
#include "../../external/qcustomplot.h"
#include "UIUtils.h"

VisualizationWindow::VisualizationWindow(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);
}

void VisualizationWindow::init(const QList<PresentationRecord> &records, QString &memberName, QDate &startDate, QDate &endDate) {

    QList<PresentationRecord> recordsInRange = filterByDateRange(records, startDate, endDate);
    QList<PresentationRecord> recordsMatchingMember;
    ui.GraphTitleLabel->setText("Visualization for " + memberName);
    ui.GraphTitleLabel->setAlignment(Qt::AlignHCenter);
    ui.DateRangeLabel->setText(startDate.toString("'From' MMMM d',' yyyy") +
                                endDate.toString("' to' MMMM d',' yyyy"));
    ui.DateRangeLabel->setAlignment(Qt::AlignHCenter);

    setWindowTitle("Visualizations - " + memberName);

    // all records matching the given member
    for (const PresentationRecord &record : recordsInRange) {
        if (record.memberName == memberName) {
            recordsMatchingMember.append(record);
        }
    }

    QSet<QString> typeSet;
    QMap<QString, int> typeMap;
    // from records matching member, we need each unique type, and the count
    for (const PresentationRecord &record : recordsMatchingMember) {
        typeSet.insert(record.type);
        ++typeMap[record.type];
    }

    QVector<QString> labels;
    QVector<double> valueData;
    QVector<double> ticks;
    int tickCount = 1;
    int valueMax = 0;
    // transform the set and map into something usable by the bargraph
    for (const QString type : typeSet) {
        if (type == " " || type == "") {
            labels << "Unnamed";
        } else {
            labels << type;
        }

        ticks << tickCount++;
        double valD = (double) typeMap[type];
        valueData << valD;

        if (valD > valueMax) {
            valueMax = valD;
        }
    }

    QCPBars *barGraph = new QCPBars(ui.Visualization->xAxis, ui.Visualization->yAxis);
    ui.Visualization->addPlottable(barGraph);

    // bar outline thickness
    QPen pen;
    pen.setWidthF(1.2);
    barGraph->setPen(pen);

    /* x axis */
    ui.Visualization->xAxis->setAutoTicks(false);
    ui.Visualization->xAxis->setAutoTickLabels(false);
    ui.Visualization->xAxis->setTickVector(ticks);
    ui.Visualization->xAxis->setTickVectorLabels(labels);
    ui.Visualization->xAxis->setTickLabelRotation(60);
    ui.Visualization->xAxis->setTickLength(0, 4);
    ui.Visualization->xAxis->grid()->setVisible(true);
    ui.Visualization->xAxis->setSubTickCount(0);
    ui.Visualization->xAxis->setRange(0, tickCount);

    /* y axis */

    // these four methods force the y-axis to increment integers only
    ui.Visualization->yAxis->setAutoTickStep(false);
    ui.Visualization->yAxis->setAutoSubTicks(false);
    ui.Visualization->yAxis->setSubTickCount(0);
    ui.Visualization->yAxis->setRange(0, valueMax + 0.1);
    ui.Visualization->yAxis->setTickStep(1);

    // info for graph name should be sent in the method call?
    barGraph->setName("Test name 1");
    barGraph->setData(ticks, valueData);
}
