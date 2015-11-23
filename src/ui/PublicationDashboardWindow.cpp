#include <cstdlib>
#include <exception>
#include <QtGlobal>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QPair>
#include <QDebug>
#include <QTreeWidgetItem>

#include "TeachingDashboardWindow.h"
#include "../records/TeachingRecord.h"
#include "../parser/TeachingParser.h"
#include "UIUtils.h"
#include "VisualizationWindow.h"

static const int facultyMemberNameColumn = 3;


TeachingDashboardWindow::TeachingDashboardWindow(QString csv_filename) {
	TeachingParser parser;
	
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
                                                "" << "Published Type"  << "Faculty Name" << "Total");
	
        ui.subjectAreaLabel->setText("Publication Summary");
	ui.departmentLabel->setText("Department of " + records[0].primaryDomain);
	ui.statusbar->showMessage("Read " + QString::number(records.size()) + " records from " + csv_filename);
        setWindowTitle("Publication - " + records[0].primaryDomain + " - " + csv_filename);
	
	QPair<QDate, QDate> dateInterval = findDateRangeStartEnd(records);
	ui.startDateSelector->setDate(dateInterval.first);
	ui.endDateSelector->setDate(dateInterval.second);
	
	updateDateLabel();
	updateTreeWidget();
}

void TeachingDashboardWindow::updateTreeWidget() {
	ui.treeWidget->clear();
	
	//find records in range
	QList<TeachingRecord> recordsInRange = filterByDateRangeStartEnd(records,
												ui.startDateSelector->date(),
												ui.endDateSelector->date());
        //count the records
        QMap<QString, int> typeSummary;
        QMap<QString, QMap<QString, int>> nameSummary;

        for (const PresentationRecord &record : recordsInRange) {
            ++typeTypeSummary[record.type];
            ++nameSummary[record.type][record.memberName];
        }

        //build the view
        QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, (QStringList() <<
                                                                        "Publication" << "" << "" << QString::number(recordsInRange.size())));
        ui.treeWidget->expandItem(root);

        for (auto pubType = typeSummary.begin(); pubType != typeSummary.end(); ++pubType) {
        QTreeWidgetItem *typeNode = new QTreeWidgetItem(root, (QStringList() <<
                                                                                        "" << pubType.key() << "" << QString::number(pubType.value())));

                QMap<QString, int> &currNameSummary = nameSummary[presType.key()];
                for (auto name = currNameSummary.begin(); name != currNameSummary.end(); ++name) {
                     new QTreeWidgetItem(typeNode, (QStringList() <<
                                        "" << "" << name.key() << QString::number(name.value())));
                }
        }

    setColumnWidths();
}


//Opens a VisualizationWindow if the row that was doubleclicked contains a faculty member
void TeachingDashboardWindow::on_treeWidget_doubleClicked() {
	/*
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
    */
}
