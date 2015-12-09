#ifndef PRESENTATIONDASHBOARDWINDOW_H
#define PRESENTATIONDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/PresentationRecord.h"

class PresentationDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
	PresentationDashboardWindow(const QString &csv_filename);
	
 protected:
	virtual void updateTreeWidget();
	virtual void openVisualizationWindow(const QString &memberName);
	inline virtual int memberNameColumn() {
		return 2;
	}

 private:
	QList<PresentationRecord> records;
};

#endif
