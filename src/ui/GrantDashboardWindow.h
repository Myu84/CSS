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
	
 protected slots:
    virtual void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item);
    virtual void on_openVisualizationButton_clicked();
	
 protected:
	virtual void updateTreeWidget();

 private:
	void openVisualizationWindow(const QString &memberName);
	
	QList<GrantRecord> records;
};

#endif
