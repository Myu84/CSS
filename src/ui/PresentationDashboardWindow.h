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
	
 protected slots:
    virtual void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item);
	virtual void on_openVisualizationButton_clicked();
	
 protected:
	virtual void updateTreeWidget();

 private:
	void openVisualizationWindow(const QString &memberName);

	QList<PresentationRecord> records;
};

#endif
