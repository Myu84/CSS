#include <QApplication>
#include <QMessageBox>

#include "ui/DashboardWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
		
	DashboardWindow dashboard;
	dashboard.show();
	
	return app.exec();
}
