#ifndef FILEINPUTDIALOG_H
#define FILEINPUTDIALOG_H

#include <QString>
#include <QDialog>

#include "ui_FileInputDialog.h"

enum SubjectArea {
	None, Publications, Presentation, Grants, Teaching
};

class FileInputDialog : public QDialog {
	Q_OBJECT

 public:
	FileInputDialog();
	
	inline QString getFilename() {
		return filename;
	}
	inline SubjectArea getSubjectArea() {
		return subjectArea;
	}
	
 private slots:
	void on_browseButton_clicked();
	
	void on_okCancelButtons_accepted();
	inline void on_okCancelButtons_rejected() {
		reject();
	}
	
	inline void on_publicationsButton_clicked() {
		subjectArea = Publications;
	}
	void on_presentationButton_clicked() {
		subjectArea = Presentation;
	}
	void on_grantsButton_clicked() {
		subjectArea = Grants;
	}
	void on_teachingButton_clicked() {
		subjectArea = Teaching;
	}

 private:
	Ui::FileInputDialog ui;
	
	QString filename;
	SubjectArea subjectArea = None;
};

#endif
