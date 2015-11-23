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

static const int memberNameColumn = 2;

PublicationDashboardWindow::PublicationDashboardWindow(QString csv_filename) {
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
						"" << "Publication Type" << "Faculty Name" << "Total");

	ui.subjectAreaLabel->setText("Publication Summary");
	ui.departmentLabel->setText("Department of " + records[0].primaryDomain);
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

	for (const PublicationRecord &record : recordsInRange) {
		++pubTypeSummary[record.type];

		++nameSummary[record.type][record.memberName];
	}

	//build the view
	QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, (QStringList() <<
									"Publications" << "" << "" << QString::number(recordsInRange.size())));
	ui.treeWidget->expandItem(root);

	for (auto pubType = pubTypeSummary.begin(); pubType != pubTypeSummary.end(); ++pubType) {
		QTreeWidgetItem *pubNode = new QTreeWidgetItem(root, (QStringList() <<
											"" << pubType.key() << "" << QString::number(pubType.value())));

		QMap<QString, int> &currNameSummary = nameSummary[pubType.key()];
		for (auto name = currNameSummary.begin(); name != currNameSummary.end(); ++name) {
			new QTreeWidgetItem(pubNode, (QStringList() <<
					"" << "" << name.key() << QString::number(name.value())));
		}
	}

    setColumnWidths();
}

//Opens a VisualizationWindow if the row that was doubleclicked contains a faculty member
void PublicationDashboardWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item) {
    QString memberName = item->text(memberNameColumn);
	if (memberName.isEmpty())
		return;

	QDate startDate = ui.startDateSelector->date();
	QDate endDate = ui.endDateSelector->date();
	
	QList<PublicationRecord> recordsInRange = filterByDateRange(records, startDate, endDate);
	
	//count the records
	QMap<QString, double> pubTypeSummary;
	for (const PublicationRecord &record : recordsInRange) {
		if (record.memberName == memberName) {
			++pubTypeSummary[record.type];
		}
	}
	
    //open a VisualizationWindow
	VisualizationWindow *vw = new VisualizationWindow({pubTypeSummary}, {"Publication Types"}, 
													  memberName, startDate, endDate);
	vw->exec();
}
