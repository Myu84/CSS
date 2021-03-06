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

static const int totalNumColumn = 4;

PresentationDashboardWindow::PresentationDashboardWindow(const QString &csv_filename) {
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
						"" << "Presentation Type" << "Faculty Name" << "Title" << "Total #" << "");
	
	ui.titleLabel->setText("Presentations Summary, Department of " + records[0].primaryDomain);
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
	QMap<QString, QMap<QString, QSet<QString>>> titleSummary;
	
	for (const PresentationRecord &record : recordsInRange) {
        ++presTypeSummary[record.type];
		
        ++nameSummary[record.type][record.memberName];
		
		titleSummary[record.type][record.memberName].insert(record.title);
	}
	
	//build the view
    QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, (QStringList() << 
									"Presentations" << "" << "" << "" << QString::number(recordsInRange.size())));
	root->setTextAlignment(totalNumColumn, Qt::AlignRight);
	ui.treeWidget->expandItem(root);
	
	for (auto presType = presTypeSummary.begin(); presType != presTypeSummary.end(); ++presType) {
        QTreeWidgetItem *presNode = new QTreeWidgetItem(root, (QStringList() << 
											"" << presType.key() << "" << "" << QString::number(presType.value())));
		presNode->setTextAlignment(totalNumColumn, Qt::AlignRight);
		
		QMap<QString, int> &currNameSummary = nameSummary[presType.key()];
		for (auto name = currNameSummary.begin(); name != currNameSummary.end(); ++name) {
            QTreeWidgetItem *nameNode = new QTreeWidgetItem(presNode, (QStringList() << 
												"" << "" << name.key() << "" << QString::number(name.value())));
			nameNode->setTextAlignment(totalNumColumn, Qt::AlignRight);
			
			QSet<QString> &currTitleSummary = titleSummary[presType.key()][name.key()];
			for (QString &title : sortSet(currTitleSummary)) {
				QTreeWidgetItem *titleNode = new QTreeWidgetItem(nameNode, (QStringList() <<
												"" << "" << "" << title << ""));
				titleNode->setTextAlignment(totalNumColumn, Qt::AlignRight);
			}
		}
	}

	//set the dropdown values
	ui.visualizationFacultyNameSelector->clear();
	ui.visualizationFacultyNameSelector->addItems(listFacultyNames(recordsInRange));
	
    setColumnWidths();
}

void PresentationDashboardWindow::openVisualizationWindow(const QString &memberName) {
	QDate startDate = ui.startDateSelector->date();
	QDate endDate = ui.endDateSelector->date();
	
	QList<PresentationRecord> recordsInRange = filterByDateRange(records, startDate, endDate);
	
	//count the records
	QMap<QString, double> presTypeSummary;
	QMap<QString, double> roleSummary;
	for (const PresentationRecord &record : recordsInRange) {
		if (record.memberName == memberName) {
			++presTypeSummary[record.type];
			++roleSummary[record.role];
		}
	}
	
    QList<QMap<QString, double>> plotList;
    plotList << presTypeSummary << roleSummary;

    QList<QString> plotNames;
    plotNames << "Presentation Types" << "Roles";
	
    //open a VisualizationWindow
    VisualizationWindow *vw = new VisualizationWindow(plotList, plotNames,
													  memberName, startDate, endDate);
	vw->show();
}
