#ifndef GRANTDASHBOARDWINDOW_H
#define GRANTDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/GrantRecord.h"

class GrantDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
	GrantDashboardWindow(QString csv_filename);
	
 protected slots:
    virtual void on_treeWidget_doubleClicked();
	
 protected:
	virtual void updateTreeWidget();

 private:
	QList<GrantRecord> records;
};

#endif
