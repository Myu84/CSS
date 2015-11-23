#ifndef PUBLICATIONDASHBOARDWINDOW_H
#define PUBLICATIONDASHBOARDWINDOW_H

#include <QString>
#include <QList>

#include "DashboardWindow.h"
#include "../records/PublicationRecord.h"

class PublicationDashboardWindow : public DashboardWindow {
	Q_OBJECT

 public:
        PublicationDashboardWindow(QString csv_filename);
	
 protected slots:
    virtual void on_treeWidget_doubleClicked();
	
 protected:
	virtual void updateTreeWidget();

 private:
        QList<PublicationRecord> records;
};

#endif
