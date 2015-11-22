#include <cstdlib>
#include <QtGlobal>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QPair>
#include <QTreeWidgetItem>

#include "TeachingDashboardWindow.h"
#include "../records/TeachingRecord.h"
#include "../parser/TeachingParser.h"
#include "UIUtils.h"
#include "VisualizationWindow.h"

static const int facultyMemberNameColumn = 3;

QString toAcademicYear(const QDate &date) {
	if (date.month() < 9) { //before September 1
		return QString::number(date.year());
	} else { //after September 1
		return QString::number(date.year() + 1);
	}
}

QString shortProgramName(QString program) {
	return program.replace("Undergraduate Medical Education", "UME", Qt::CaseInsensitive)
				  .replace("Postgraduate Medical Education", "PME", Qt::CaseInsensitive)
				  .replace("Continuing Medical Education", "CME", Qt::CaseInsensitive);
}

TeachingDashboardWindow::TeachingDashboardWindow(QString csv_filename) {
	TeachingParser parser;
	
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
						"" << "Program" << "Academic Year" << "Faculty Name" << "Hours" << "Students");
	
	ui.subjectAreaLabel->setText("Teaching Summary");
	ui.departmentLabel->setText("Department of " + records[0].primaryDomain);
	ui.statusbar->showMessage("Read " + QString::number(records.size()) + " records from " + csv_filename);
	setWindowTitle("Teaching - " + records[0].primaryDomain + " - " + csv_filename);
	
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

    //total the records
	QPair<double, uint> allSummary;
    QMap<QString, QPair<double, uint>> programSummary;
    QMap<QString, QMap<QString, QPair<double, uint>>> yearSummary;
    QMap<QString, QMap<QString, QMap<QString, QPair<double, uint>>>> nameSummary;

	for (const TeachingRecord &record : recordsInRange) {
		QString programName = shortProgramName(record.program);
		QString academicYear = toAcademicYear(record.startDate);
		
		allSummary.first += record.totalHours;
        allSummary.second += record.numTrainees;
		
		programSummary[programName].first += record.totalHours;
        programSummary[programName].second += record.numTrainees;
		
		yearSummary[programName][academicYear].first += record.totalHours;
        yearSummary[programName][academicYear].second += record.numTrainees;
		
        nameSummary[programName][academicYear][record.memberName].first += record.totalHours;
        nameSummary[programName][academicYear][record.memberName].second += record.numTrainees;
	}

    //build the view
    QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, (QStringList() << 
									"Teaching" << "" << "" << "" << QString::number(allSummary.first) << QString::number(allSummary.second)));
	ui.treeWidget->expandItem(root);
	
	for (auto program = programSummary.begin(); program != programSummary.end(); ++program) {
        QTreeWidgetItem *programNode = new QTreeWidgetItem(root, (QStringList() << 
											"" << program.key() << "" << "" << QString::number(program.value().first) << QString::number(program.value().second)));
		
		QMap<QString, QPair<double, uint>> &currYearSummary = yearSummary[program.key()];
		for (auto year = currYearSummary.begin(); year != currYearSummary.end(); ++year) {
            QTreeWidgetItem *yearNode = new QTreeWidgetItem(programNode, (QStringList() << 
												"" << "" << year.key() << "" << QString::number(year.value().first) << QString::number(year.value().second)));
		
			QMap<QString, QPair<double, uint>> &currNameSummary = nameSummary[program.key()][year.key()];
			for (auto name = currNameSummary.begin(); name != currNameSummary.end(); ++name) {
				new QTreeWidgetItem(yearNode, (QStringList() << 
						"" << "" << "" << name.key() << QString::number(name.value().first) << QString::number(name.value().second)));
			}
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
