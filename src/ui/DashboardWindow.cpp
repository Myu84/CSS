#include <cassert>

#include "FileInputDialog.h"
#include "DashboardWindow.h"
#include "PresentationDashboardWindow.h"
#include "ui_DashboardWindow.h"

DashboardWindow::DashboardWindow() {
    ui.setupUi(this);
}

DashboardWindow *DashboardWindow::makeDashboard() {
	FileInputDialog inputDialog;
	if (inputDialog.exec() == QDialog::Accepted) {
		if (inputDialog.getSubjectArea() == Presentation) {
			return new PresentationDashboardWindow(inputDialog.getFilename());
		} else {
			throw "Unimplemented subject area";
		}
	} else {
		return nullptr;
	}
}
