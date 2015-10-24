#include "PresentationDashboardWindow.h"
#include "../records/PresentationRecord.h"
#include "../parser/PresentationParser.h"

PresentationDashboardWindow::PresentationDashboardWindow(std::string csv_filename) {
    PresentationParser parser;
	records = parser.parse(csv_filename);
}

