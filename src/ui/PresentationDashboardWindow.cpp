#include <cstdlib>
#include <exception>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QPair>
#include <QDebug>
#include <QTreeWidgetItem>

#include "PresentationDashboardWindow.h"
#include "../records/PresentationRecord.h"
#include "../parser/PresentationParser.h"
#include "UIUtils.h"
#include "VisualizationWindow.h"

static const int memberNameColumn = 2;

PresentationDashboardWindow::PresentationDashboardWindow(QString csv_filename) {
	PresentationParser parser;
	
	try {
		records = parser.parse(csv_filename);
	} catch (const std::exception &e) {
		qDebug() << e.what();
		QMessageBox::critical(this, "Error", "A fatal error occurred while parsing the CSV file");
		exit(1);
	}
	
	if (records.empty()) {
		QMessageBox::critical(this, "Error", "The CSV file has no records");
		exit(1);
	}
	
	ui.treeWidget->setHeaderLabels(QStringList() << 
						"" << "Presentation Type" << "Faculty Name" << "Total #");
	
	ui.subjectAreaLabel->setText("Presentations Summary");
	ui.departmentLabel->setText("Department of " + records[0].primaryDomain);
	ui.statusbar->showMessage("Read " + QString::number(records.size()) + " records from " + csv_filename);
	setWindowTitle("Presentations - " + records[0].primaryDomain + " - " + csv_filename);
	
	QPair<QDate, QDate> dateInterval = findDateRange(records);
	ui.startDateSelector->setDate(dateInterval.first);
	ui.endDateSelector->setDate(dateInterval.second);
	
	updateDateLabel();
	updateTreeWidget();
}

void PresentationDashboardWindow::updateTreeWidget() {
	ui.treeWidget->clear();
	
	//find records in range
	QList<PresentationRecord> recordsInRange = filterByDateRange(records, 
													ui.startDateSelector->date(),
													ui.endDateSelector->date());
	
	//count the records
	QMap<QString, int> presTypeSummary;
	QMap<QString, QMap<QString, int>> nameSummary;
	
	for (const PresentationRecord &record : recordsInRange) {
        ++presTypeSummary[record.type];
		
        ++nameSummary[record.type][record.memberName];
	}
	
	//build the view
    QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, (QStringList() << 
									"Presentations" << "" << "" << QString::number(recordsInRange.size())));
	ui.treeWidget->expandItem(root);
	
	for (auto presType = presTypeSummary.begin(); presType != presTypeSummary.end(); ++presType) {
        QTreeWidgetItem *presNode = new QTreeWidgetItem(root, (QStringList() << 
											"" << presType.key() << "" << QString::number(presType.value())));
		
		QMap<QString, int> &currNameSummary = nameSummary[presType.key()];
		for (auto name = currNameSummary.begin(); name != currNameSummary.end(); ++name) {
            new QTreeWidgetItem(presNode, (QStringList() << 
					"" << "" << name.key() << QString::number(name.value())));
		}
	}

    setColumnWidths();
}

//Opens a VisualizationWindow if the row that was doubleclicked contains a faculty member
void PresentationDashboardWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item) {
    QString memberName = item->text(memberNameColumn);
	if (memberName.isEmpty())
		return;

	QDate startDate = ui.startDateSelector->date();
	QDate endDate = ui.endDateSelector->date();
	
	QList<PresentationRecord> recordsInRange = filterByDateRange(records, startDate, endDate);
	
	//count the records
	QMap<QString, double> presTypeSummary;
	for (const PresentationRecord &record : recordsInRange) {
		if (record.memberName == memberName) {
			++presTypeSummary[record.type];
		}
	}
	
    QList<QMap<QString, double>> plotList;
    plotList << presTypeSummary;

    QList<QString> plotNames;
    plotNames << "Presentation Types";
	
    //open a VisualizationWindow
    VisualizationWindow *vw = new VisualizationWindow(plotList, plotNames,
													  memberName, startDate, endDate);
	vw->show();
}
