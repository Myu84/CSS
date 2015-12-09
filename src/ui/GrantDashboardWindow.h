#ifndef GRANTDASHBOARDWINDOW_H
#define GRANTDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/GrantRecord.h"

class GrantDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
	GrantDashboardWindow(const QString &csv_filename);
	
 protected:
	virtual void updateTreeWidget();
	virtual void openVisualizationWindow(const QString &memberName);
	inline virtual int memberNameColumn() {
		return 3;
	}

 private:
	QList<GrantRecord> records;
};

#endif
