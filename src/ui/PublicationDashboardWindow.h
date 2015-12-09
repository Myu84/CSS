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
	
 protected:
	virtual void updateTreeWidget();
	virtual void openVisualizationWindow(const QString &memberName);
	inline virtual int memberNameColumn() {
		return 2;
	}

 private:
    QList<PublicationRecord> records;
};

#endif
