#include <cstdlib>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QPair>
#include <QTreeWidgetItem>

#include "PresentationDashboardWindow.h"
#include "../records/PresentationRecord.h"
#include "../parser/PresentationParser.h"
#include "UIUtils.h"
#include "VisualizationWindow.h"

static const int facultyMemberNameColumn = 2;

PresentationDashboardWindow::PresentationDashboardWindow(QString csv_filename) {
	PresentationParser parser;
	
	try {
		records = parser.parse(csv_filename);
	} catch (...) {
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
void PresentationDashboardWindow::on_treeWidget_doubleClicked() {
    //Gets the row that was doubleclicked; I believe selectedItems() only returns what has keyboard focus, which can only be one row in our case
    //Therefore it should work because it can only ever return the one line that was doubleclicked; still kind of hacky though
    QTreeWidgetItem *selected = ui.treeWidget->selectedItems().first();

    //If the row contains a faculty member name, it's graphable so open a VisualizationWindow
    if (selected->text(facultyMemberNameColumn) != "") {
        VisualizationWindow vw(this);
		
        QString memberName = selected->text(facultyMemberNameColumn);
        QDate sDate = ui.startDateSelector->date();
        QDate eDate = ui.endDateSelector->date();
        vw.init(records, memberName, sDate, eDate);
        vw.exec();
    }
}
