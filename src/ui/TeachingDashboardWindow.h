#ifndef TEACHINGDASHBOARDWINDOW_H
#define TEACHINGDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/TeachingRecord.h"

class TeachingDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
	TeachingDashboardWindow(QString csv_filename);//constructor
	
 protected:
	virtual void updateTreeWidget();
	
    virtual void on_treeWidget_doubleClicked();

 private://attributes
	QList<TeachingRecord> records;
};

#endif
