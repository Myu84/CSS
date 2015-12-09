#include <QMessageBox>
#include <QFileDialog>
#include <QString>

#include "FileInputDialog.h"
#include "ui_FileInputDialog.h"

FileInputDialog::FileInputDialog() {
    ui.setupUi(this);
	setFixedSize(size());
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

void FileInputDialog::on_browseButton_clicked() {
	filename = QFileDialog::getOpenFileName(this, "Select Input CSV File", "", 
											"CSV Files (*.csv)");
	ui.filenameText->setText(filename);
}
