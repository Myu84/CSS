#include <cstdlib>
#include <exception>
#include <QtGlobal>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QPair>
#include <QDebug>
#include <QTreeWidgetItem>

#include "PublicationDashboardWindow.h"
#include "../records/PublicationRecord.h"
#include "../parser/PublicationParser.h"
#include "UIUtils.h"
#include "VisualizationWindow.h"

static const int totalNumColumn = 4;

PublicationDashboardWindow::PublicationDashboardWindow(const QString &csv_filename) {
	PublicationParser parser;

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
						"" << "Publication Type" << "Faculty Name" << "Title" << "Total #" << "");

	ui.titleLabel->setText("Publication Summary, Department of " + records[0].primaryDomain);
	ui.statusbar->showMessage("Read " + QString::number(records.size()) + " records from " + csv_filename);
	setWindowTitle("Publication - " + records[0].primaryDomain + " - " + csv_filename);

	QPair<QDate, QDate> dateInterval = findDateRange(records);
	ui.startDateSelector->setDate(dateInterval.first);
	ui.endDateSelector->setDate(dateInterval.second);

	updateDateLabel();
	updateTreeWidget();
}

void PublicationDashboardWindow::updateTreeWidget() {
	ui.treeWidget->clear();

	//find records in range
	QList<PublicationRecord> recordsInRange = filterByDateRange(records,
												ui.startDateSelector->date(),
												ui.endDateSelector->date());

	//count the records
	QMap<QString, int> pubTypeSummary;
	QMap<QString, QMap<QString, int>> nameSummary;
	QMap<QString, QMap<QString, QSet<QString>>> titleSummary;

	for (const PublicationRecord &record : recordsInRange) {
		++pubTypeSummary[record.type];

		++nameSummary[record.type][record.memberName];
		
		titleSummary[record.type][record.memberName].insert(record.title);
	}

	//build the view
	QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, (QStringList() <<
									"Publications" << "" << "" << "" << QString::number(recordsInRange.size())));
	root->setTextAlignment(totalNumColumn, Qt::AlignRight);
	ui.treeWidget->expandItem(root);

	for (auto pubType = pubTypeSummary.begin(); pubType != pubTypeSummary.end(); ++pubType) {
		QTreeWidgetItem *pubNode = new QTreeWidgetItem(root, (QStringList() <<
											"" << pubType.key() << "" << "" << QString::number(pubType.value())));
		pubNode->setTextAlignment(totalNumColumn, Qt::AlignRight);
		
		QMap<QString, int> &currNameSummary = nameSummary[pubType.key()];
		for (auto name = currNameSummary.begin(); name != currNameSummary.end(); ++name) {
			QTreeWidgetItem *nameNode = new QTreeWidgetItem(pubNode, (QStringList() <<
												"" << "" << name.key() << "" << QString::number(name.value())));
			nameNode->setTextAlignment(totalNumColumn, Qt::AlignRight);
			
			QSet<QString> &currTitleSummary = titleSummary[pubType.key()][name.key()];
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

void PublicationDashboardWindow::openVisualizationWindow(const QString &memberName) {
	QDate startDate = ui.startDateSelector->date();
	QDate endDate = ui.endDateSelector->date();
	
	QList<PublicationRecord> recordsInRange = filterByDateRange(records, startDate, endDate);
	
	//count the records
	QMap<QString, double> pubTypeSummary;
	QMap<QString, double> statusSummary;
	QMap<QString, double> roleSummary;
	QMap<QString, double> publishedInSummary;
	for (const PublicationRecord &record : recordsInRange) {
		if (record.memberName == memberName) {
			++pubTypeSummary[record.type];
			++statusSummary[record.publicationStatus];
			++roleSummary[record.role];
			++publishedInSummary[record.publishedIn];
		}
	}

    QList<QMap<QString, double>> plotList;
    plotList << pubTypeSummary << statusSummary << roleSummary << publishedInSummary;
	
    QList<QString> plotNames;
    plotNames << "Publication Types" << "Publication Status" << "Roles" << "Published In";

    //open a VisualizationWindow
    VisualizationWindow *vw = new VisualizationWindow(plotList, plotNames,
													  memberName, startDate, endDate);
	vw->show();
}
