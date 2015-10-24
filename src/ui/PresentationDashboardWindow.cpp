#include <cstdlib>
#include <QMessageBox>

#include "PresentationDashboardWindow.h"
#include "../records/PresentationRecord.h"
#include "../parser/PresentationParser.h"

PresentationDashboardWindow::PresentationDashboardWindow(std::string csv_filename) {
    PresentationParser parser;
	
	try {
		records = parser.parse(csv_filename);
	} catch (...) {
		QMessageBox::critical(this, "Error", "A fatal error occurred while parsing the CSV file");
		exit(1);
	}
	
	/*
		Display the records here
	*/
}
