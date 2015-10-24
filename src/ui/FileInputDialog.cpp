#include <QMessageBox>
#include <QFileDialog>

#include "FileInputDialog.h"
#include "ui_FileInputDialog.h"

FileInputDialog::FileInputDialog(QWidget *parent) : QDialog(parent) {
    ui.setupUi(this);
	ui.setFixedSize(ui.size());
}

std::string FileInputDialog::getFilename() {
	return filename;
}

SubjectArea FileInputDialog::getSubjectArea() {
	return subjectArea;
}

void FileInputDialog::on_okCancelButtons_accepted() {
	if (subjectArea == None) {
		QMessageBox::critical(this, "Error", "You must select a subject area");
	} else if (filename.empty()) {
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
	QString str = QFileDialog::getOpenFileName(this, "Select Input CSV File", "", 
											   "CSV Files (*.csv)");
	ui.filenameText->setText(str);
	filename = str.toStdString();
}
