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
	
 protected slots:
    virtual void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item);
	virtual void on_openVisualizationButton_clicked();
	
 protected:
	virtual void updateTreeWidget();

 private:
	void openVisualizationWindow(const QString &memberName);
	
	QList<TeachingRecord> records;
};

#endif
