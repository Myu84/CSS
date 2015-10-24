#ifndef PRESENTATIONDASHBOARDWINDOW_H
#define PRESENTATIONDASHBOARDWINDOW_H

#include <vector>

#include "DashboardWindow.h"
#include "../records/PresentationRecord.h"

class PresentationDashboardWindow : public DashboardWindow {
    Q_OBJECT

 public:
    PresentationDashboardWindow(std::string csv_filename);

 private:
	vector<PresentationRecord> records;
};

#endif
