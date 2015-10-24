#include "DashboardWindow.h"
#include "ui_DashboardWindow.h"

DashboardWindow::DashboardWindow() : QMainWindow() {
	//show the file chooser dialog
	FileInputDialog fileInputDialog;
	if (fileInputDialog.exec() == QDialog::Accepted) {
		//launch the dashboard
		
	} else {
		return 0;
	}
	
    ui.setupUi(this);
}
