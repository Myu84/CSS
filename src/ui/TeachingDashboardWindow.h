#ifndef TEACHINGDASHBOARDWINDOW_H
#define TEACHINGDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/TeachingRecord.h"

class TeachingDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
	TeachingDashboardWindow(QString csv_filename);
	
 protected slots:
    virtual void on_treeWidget_doubleClicked();
	
 protected:
	virtual void updateTreeWidget();

 private:
	QList<TeachingRecord> records;
};

#endif
