#ifndef PUBLICATIONDASHBOARDWINDOW_H
#define PUBLICATIONDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/PublicationRecord.h"

class PublicationDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
    PublicationDashboardWindow(const QString &csv_filename);
	
 protected slots:
    virtual void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item);
	virtual void on_openVisualizationButton_clicked();
	
 protected:
	virtual void updateTreeWidget();

 private:
	void openVisualizationWindow(const QString &memberName);
	
    QList<PublicationRecord> records;
};

#endif
