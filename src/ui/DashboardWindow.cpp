#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QDesktopWidget>
#include <QRect>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QtGlobal>

#include "FileInputDialog.h"
#include "DashboardWindow.h"
#include "PresentationDashboardWindow.h"
#include "TeachingDashboardWindow.h"
#include "GrantDashboardWindow.h"
#include "PublicationDashboardWindow.h"
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
        else if (inputDialog.getSubjectArea() == Teaching) {
            return new TeachingDashboardWindow(inputDialog.getFilename());
        }
        else if (inputDialog.getSubjectArea() == Grants) {
            return new GrantDashboardWindow(inputDialog.getFilename());
        }
        else if (inputDialog.getSubjectArea() == Publications) {
            return new PublicationDashboardWindow(inputDialog.getFilename());
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
							   ui.startDateSelector->date().toString("MMM d yyyy") + 
							   " to " + 
							   ui.endDateSelector->date().toString("MMM d yyyy"));
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

int treeWidgetToTextTable(QTreeWidgetItem *item, QTextTable *table, int rowNum) {
	for (int c = 0; c < item->childCount(); ++c) {
		QTreeWidgetItem *child = item->child(c);
		
		//export child
		table->appendRows(1);
		for (int colNum = 0; colNum < child->columnCount(); ++colNum) {
			table->cellAt(rowNum, colNum).firstCursorPosition().insertText(child->text(colNum));
		}
		++rowNum;
		
		//recurse to children
		if (child->isExpanded() && child->childCount() > 0) {
			rowNum = treeWidgetToTextTable(child, table, rowNum);
		}
	}
	
	return rowNum;
}

void DashboardWindow::printTreeWidget(QPrinter *printer) {
	//build a table
    QTextDocument doc;
	QTextCursor cursor(&doc);
	QTextTable *table = cursor.insertTable(1, ui.treeWidget->columnCount());
	
	//header
	for (int colNum = 0; colNum < ui.treeWidget->columnCount(); ++colNum) {
		table->cellAt(0, colNum).firstCursorPosition().insertText(ui.treeWidget->headerItem()->text(colNum));
	}
	
	//table content
	treeWidgetToTextTable(ui.treeWidget->invisibleRootItem(), table, 1);
	
	doc.print(printer);
}

void DashboardWindow::on_actionPrint_triggered() {
    // set up the printer
    QPrinter printer;

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print Document"));

    if (dialog.exec() != QDialog::Accepted)
        return;

    printTreeWidget(&printer);
}

void DashboardWindow::on_actionExport_triggered() {
    // set up the printer
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Dashboard"), "", tr("PDF (.*pdf)"));
	if (filename.isEmpty())
		return;
	
    QPrinter printer(QPrinter::HighResolution);
	printer.setOutputFormat(QPrinter::PdfFormat);
	printer.setOutputFileName(filename);

    printTreeWidget(&printer);
}
