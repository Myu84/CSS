#include <cstdlib>
#include <QMessageBox>
#include <QString>

#include "PresentationDashboardWindow.h"
#include "../records/PresentationRecord.h"
#include "../parser/PresentationParser.h"

PresentationDashboardWindow::PresentationDashboardWindow(QString csv_filename) {
    PresentationParser parser;
	
	try {
		records = parser.parse(csv_filename);
	} catch (...) {
		QMessageBox::critical(this, "Error", "A fatal error occurred while parsing the CSV file");
		exit(1);
	}
	
	ui.subjectAreaLabel->setText("Presentations");
	ui.departmentLabel->setText(records[0].primaryDomain);
	ui.statusbar->showMessage("Read " + QString::number(records.size()) + " records from " + csv_filename);
	setWindowTitle("Presentations - " + records[0].primaryDomain + " - " + csv_filename);
	
	/*
		Display the records here
	*/
}
