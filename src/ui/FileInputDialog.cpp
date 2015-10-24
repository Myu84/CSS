#include <QMessageBox>
#include <QFileDialog>
#include <QString>

#include "FileInputDialog.h"
#include "ui_FileInputDialog.h"

FileInputDialog::FileInputDialog(QWidget *parent) : QDialog(parent) {
    ui.setupUi(this);
	setFixedSize(size());
}

QString FileInputDialog::getFilename() {
	return filename;
}

SubjectArea FileInputDialog::getSubjectArea() {
	return subjectArea;
}

void FileInputDialog::on_okCancelButtons_accepted() {
	if (subjectArea == None) {
		QMessageBox::critical(this, "Error", "You must select a subject area");
	} else if (filename.isEmpty()) {
		QMessageBox::critical(this, "Error", "You must select a file");
	} else {
		accept();
	}
}

void FileInputDialog::on_okCancelButtons_rejected() {
	reject();
}

void FileInputDialog::on_publicationsButton_clicked() {
	subjectArea = Publications;
}

void FileInputDialog::on_presentationButton_clicked() {
	subjectArea = Presentation;
}

void FileInputDialog::on_grantsButton_clicked() {
	subjectArea = Grants;
}

void FileInputDialog::on_teachingButton_clicked() {
	subjectArea = Teaching;
}

void FileInputDialog::on_browseButton_clicked() {
	filename = QFileDialog::getOpenFileName(this, "Select Input CSV File", "", 
											"CSV Files (*.csv)");
	ui.filenameText->setText(filename);
}
