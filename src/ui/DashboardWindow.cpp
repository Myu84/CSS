#include <QDesktopWidget>
#include <QRect>

#include "FileInputDialog.h"
#include "DashboardWindow.h"
#include "PresentationDashboardWindow.h"
#include "TeachingDashboardWindow.h"
#include "GrantDashboardWindow.h"
#include "ui_DashboardWindow.h"

DashboardWindow::DashboardWindow() {
    ui.setupUi(this);
	
	//set size to 70% of total screen size
    QDesktopWidget dw;
    QRect mainScreen = dw.availableGeometry(dw.primaryScreen());
    this->resize(mainScreen.width()*0.7, mainScreen.height()*0.7);
}

DashboardWindow *DashboardWindow::makeDashboard() {
	FileInputDialog inputDialog;
	if (inputDialog.exec() == QDialog::Accepted) {
		if (inputDialog.getSubjectArea() == Presentation) {
			return new PresentationDashboardWindow(inputDialog.getFilename());
        }
        else if(inputDialog.getSubjectArea() == Teaching){
            return new TeachingDashboardWindow(inputDialog.getFilename());
        }
        else if(inputDialog.getSubjectArea() == Grants){
            return new GrantDashboardWindow(inputDialog.getFilename());
        }
        else {
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

void DashboardWindow::setColumnWidths() {
    // for now, make sure that column width is at least equal to contents
    for (int i = 0; i < ui.treeWidget->columnCount(); i++) {
        ui.treeWidget->resizeColumnToContents(i);
    }
}

void DashboardWindow::on_treeWidget_collapsed() {
    setColumnWidths();
}

void DashboardWindow::on_treeWidget_expanded() {
    setColumnWidths();
}
