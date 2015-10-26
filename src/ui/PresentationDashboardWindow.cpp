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
#include "VisualizationWindow.h"


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
	QMap<QString, QMap<QString, int>> recordsSummary;
	for (const PresentationRecord &record : recordsInRange) {
		++recordsSummary[record.activityType][record.memberName];
	}
	
	//build the view
    QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, (QStringList() << "Presentations" << "" << "" << QString::number(recordsInRange.size())));
	ui.treeWidget->expandItem(root);


	
	for (auto presType = recordsSummary.begin(); presType != recordsSummary.end(); ++presType) {
        QTreeWidgetItem *presNode = new QTreeWidgetItem(root, (QStringList() << "" << presType.key() << "" << QString::number(total(presType.value()))));
		
		for (auto name = presType.value().begin(); name != presType.value().end(); ++name) {
            new QTreeWidgetItem(presNode, (QStringList() << "" << "" << name.key() << QString::number(name.value())));
		}
	}

    // for now, make sure that column width is at least equal to contents
    for (int i = 0; i < ui.treeWidget->columnCount(); i++) {
        ui.treeWidget->resizeColumnToContents(i);
    }
}

//Opens a VisualizationWindow if the row that was doubleclicked contains a faculty member
void PresentationDashboardWindow::on_treeWidget_doubleClicked()
{
    QTreeWidgetItem *header = ui.treeWidget->headerItem();
    int facultyMemberNameColumn = 0;
    for (int i = 0; i < ui.treeWidget->columnCount(); i++) {
        if (header->text(i) == "Faculty Name") {
            facultyMemberNameColumn = i;
        }
    }

    //Gets the row that was doubleclicked; I believe selectedItems() only returns what has keyboard focus, which can only be one row in our case
    //Therefore it should work because it can only ever return the one line that was doubleclicked; still kind of hacky though
    QTreeWidgetItem *selected = ui.treeWidget->selectedItems().first();

    //If the row contains a faculty member name, it's graphable so open a VisualizationWindow
    if(selected->text(facultyMemberNameColumn) != "") {
        VisualizationWindow vw(this);
        QString memberName = selected->text(facultyMemberNameColumn);
        QDate sDate, eDate;
        sDate = ui.startDateSelector->date();
        eDate = ui.endDateSelector->date();
        //vw.init(records, selected->text(facultyMemberNameColumn), ui.startDateSelector->date(), ui.endDateSelector->date());
        vw.init(records, memberName, sDate, eDate);
        vw.exec();
    }
}
