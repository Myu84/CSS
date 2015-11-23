#ifndef PRESENTATIONDASHBOARDWINDOW_H
#define PRESENTATIONDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/PresentationRecord.h"

class PresentationDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
	PresentationDashboardWindow(QString csv_filename);
	
 protected slots:
    virtual void on_treeWidget_doubleClicked();
	
 protected:
	virtual void updateTreeWidget();

 private:
	QList<PresentationRecord> records;
};

#endif
