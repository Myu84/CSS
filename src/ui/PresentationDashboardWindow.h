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
	
 protected:
	virtual void updateTreeWidget();
	
    virtual void on_treeWidget_doubleClicked();

 private:
	QList<PresentationRecord> records;
};

#endif
