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

QString toAcademicYear(const QDate &date) {
	if (date.month() < 9) { //before September 1
		return QString::number(date.year() - 1) + "-" + QString::number(date.year());
	} else { //after September 1
		return QString::number(date.year()) + "-" + QString::number(date.year() + 1);
	}
}

QString shortProgramName(QString program) {
	return program.replace("Undergraduate Medical Education", "UME", Qt::CaseInsensitive)
				  .replace("Postgraduate Medical Education", "PME", Qt::CaseInsensitive)
				  .replace("Continuing Medical Education", "CME", Qt::CaseInsensitive);
}

TeachingDashboardWindow::TeachingDashboardWindow(const QString &csv_filename) {
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
						"" << "Program Level" << "Academic Year" << "Faculty Name" << "Hours" << "Students");
	
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

	//set the dropdown values
	ui.visualizationFacultyNameSelector->clear();
	ui.visualizationFacultyNameSelector->addItems(listFacultyNames(recordsInRange));
	
	setColumnWidths();
}

void TeachingDashboardWindow::openVisualizationWindow(const QString &memberName) {
	QDate startDate = ui.startDateSelector->date();
	QDate endDate = ui.endDateSelector->date();
	
	QList<TeachingRecord> recordsInRange = filterByDateRangeStartEnd(records, startDate, endDate);
	
	//count the records
	QMap<QString, double> programSummaryStudents;
	QMap<QString, double> programSummaryHours;
	QMap<QString, double> typeSummaryStudents;
	QMap<QString, double> typeSummaryHours;
	for (const TeachingRecord &record : recordsInRange) {
		if (record.memberName == memberName) {
			QString programName = shortProgramName(record.program);
			
			programSummaryStudents[programName] += record.numTrainees;
			programSummaryHours[programName] += record.totalHours;
			
			typeSummaryStudents[record.activityType] += record.numTrainees;
			typeSummaryHours[record.activityType] += record.totalHours;
		}
	}

    QList<QMap<QString, double>> plotList;
    plotList << programSummaryStudents << programSummaryHours << typeSummaryStudents << typeSummaryHours;

    QList<QString> plotNames;
    plotNames << "Program Level (by # students)" << "Program Level (by total hours)" 
			  << "Activity Type (by # students)" << "Activity Type (by total hours)";
	
    //open a VisualizationWindow
    VisualizationWindow *vw = new VisualizationWindow(plotList, plotNames,
													  memberName, startDate, endDate);
	vw->show();
}
