#include "FileInputDialog.h"
#include "DashboardWindow.h"
#include "PresentationDashboardWindow.h"
#include "ui_DashboardWindow.h"
#include <QDesktopWidget>
#include <QRect>

DashboardWindow::DashboardWindow() {
    ui.setupUi(this);
    QDesktopWidget dw;
    QRect mainScreen = dw.availableGeometry(dw.primaryScreen());
    this->resize(mainScreen.width()*0.7f, mainScreen.height()*0.7f);
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

void DashboardWindow::on_dateFilterButton_clicked() {
	updateDateLabel();
	updateTreeWidget();
}

void DashboardWindow::on_actionOpen_triggered() {
    close();
    DashboardWindow *dashboard = DashboardWindow::makeDashboard();
    if (dashboard != nullptr)
        dashboard->show();

}

void DashboardWindow::updateDateLabel() {
	ui.dateRangeLabel->setText("Showing records from " + 
							   ui.startDateSelector->date().toString("yyyy/MM/dd") + 
							   " to " + 
							   ui.endDateSelector->date().toString("yyyy/MM/dd"));
}

void DashboardWindow::on_actionExit_triggered() {
	close();
}



void DashboardWindow::on_treeWidget_collapsed()
{
    // for now, make sure that column width is at least equal to contents
    for (int i = 0; i < ui.treeWidget->columnCount(); i++) {
        ui.treeWidget->resizeColumnToContents(i);
    }
}

void DashboardWindow::on_treeWidget_expanded()
{
    // for now, make sure that column width is at least equal to contents
    for (int i = 0; i < ui.treeWidget->columnCount(); i++) {
        ui.treeWidget->resizeColumnToContents(i);
    }
}
