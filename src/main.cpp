#include <QApplication>
#include <QMessageBox>

#include "ui/DashboardWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
		
	DashboardWindow *dashboard = DashboardWindow::makeDashboard();
	if (dashboard != nullptr)
		dashboard->show();
	else
		return 0;
	
	return app.exec();
}
