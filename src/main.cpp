#include <QApplication>
#include <QMessageBox>

#include "ui/FileInputDialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

	//show the file chooser dialog
	FileInputDialog fileInputDialog;
	if (fileInputDialog.exec() == QDialog::Accepted) {
		QMessageBox::information(nullptr, "Selected Filename", 
								 QString::fromStdString(fileInputDialog.getFilename()));
	} else {
		app.quit();
	}
	
    return app.exec();
}
