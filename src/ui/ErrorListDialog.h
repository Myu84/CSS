#ifndef ERRORLISTDIALOG_H
#define ERRORLISTDIALOG_H

#include <QString>
#include <QDialog>

#include "ui_ErrorListDialog.h"

class ErrorListDialog : public QDialog {
	Q_OBJECT

 public:
	ErrorListDialog(const QString &errorLog, int numErrors, int numWarnings);
	
 private slots:
	inline void on_okCancelButtons_accepted() {
		accept();
	}
	inline void on_okCancelButtons_rejected() {
		reject();
	}

 private:
	Ui::ErrorListDialog ui;
};

#endif
