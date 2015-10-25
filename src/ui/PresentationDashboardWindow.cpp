#include <cstdlib>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QPair>
#include <QTreeWidgetItem>

#include "PresentationDashboardWindow.h"
#include "../records/PresentationRecord.h"
#include "../parser/PresentationParser.h"
#include "../utils/Utils.h"

PresentationDashboardWindow::PresentationDashboardWindow(QString csv_filename) {
    PresentationParser parser;
	
	try {
		records = parser.parse(csv_filename);
	} catch (...) {
		QMessageBox::critical(this, "Error", "A fatal error occurred while parsing the CSV file");
		exit(1);
	}
	
	ui.subjectAreaLabel->setText("Presentations Summary");
	ui.departmentLabel->setText("Department of " + records[0].primaryDomain);
	ui.statusbar->showMessage("Read " + QString::number(records.size()) + " records from " + csv_filename);
	setWindowTitle("Presentations - " + records[0].primaryDomain + " - " + csv_filename);
	
	QPair<QDate, QDate> dateInterval = findDateRange(records);
	ui.startDateSelector->setDate(dateInterval.first);
	ui.endDateSelector->setDate(dateInterval.second);
	
	updateTreeWidget();
}

void PresentationDashboardWindow::updateTreeWidget() {
    ui.treeWidget->clear();
	
	//count the records
	QMap<QString, QMap<QString, int>> recordsSummary;
	for (const PresentationRecord &record : records) {
		++recordsSummary[record.activityType][record.memberName];
	}
	
	//build the view
	QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, {"Presentations", "", "", 
									QString::number(records.size())});
	
	for (auto presType = recordsSummary.begin(); presType != recordsSummary.end(); ++presType) {
		QTreeWidgetItem *presNode = new QTreeWidgetItem(root, {"", presType.key(), "", 
											QString::number(0)});
		
		for (auto name = presType.value().begin(); name != presType.value().end(); ++name) {
			new QTreeWidgetItem(presNode, {"", "", name.key(), QString::number(name.value())});
		}
	}
}
