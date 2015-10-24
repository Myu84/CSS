#ifndef PRESENTATIONDASHBOARDWINDOW_H
#define PRESENTATIONDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/PresentationRecord.h"

class PresentationDashboardWindow : public DashboardWindow {
    Q_OBJECT

 public:
    PresentationDashboardWindow(QString csv_filename);

 private:
	QList<PresentationRecord> records;
};

#endif
