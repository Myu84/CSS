#ifndef TEACHINGDASHBOARDWINDOW_H
#define TEACHINGDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/TeachingRecord.h"

class TeachingDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
	TeachingDashboardWindow(const QString &csv_filename);
	
 protected:
	virtual void updateTreeWidget();
	virtual void openVisualizationWindow(const QString &memberName);
	inline virtual int memberNameColumn() {
		return 3;
	}

 private:
	QList<TeachingRecord> records;
};

#endif
