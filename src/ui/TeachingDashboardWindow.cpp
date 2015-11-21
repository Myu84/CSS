#include <cstdlib>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QPair>
#include <QTreeWidgetItem>

#include "TeachingDashboardWindow.h"
#include "../records/TeachingRecord.h"
#include "../parser/TeachingParser.h"
#include "../utils/Utils.h"
#include "VisualizationWindow.h"


TeachingDashboardWindow::TeachingDashboardWindow(QString csv_filename) {
	TeachingParser parser;
	
	try {
		records = parser.parse(csv_filename);
	} catch (...) {
		QMessageBox::critical(this, "Error", "A fatal error occurred while parsing the CSV file");
		exit(1);
	}
	
	ui.subjectAreaLabel->setText("Teaching Summary");
	ui.departmentLabel->setText("Department of " + records[0].primaryDomain);
	ui.statusbar->showMessage("Read " + QString::number(records.size()) + " records from " + csv_filename);
	setWindowTitle("Teaching - " + records[0].primaryDomain + " - " + csv_filename);
	
	QPair<QDate, QDate> dateInterval = findDateRange(records);
	ui.startDateSelector->setDate(dateInterval.first);
	ui.endDateSelector->setDate(dateInterval.second);
	
	updateDateLabel();
	updateTreeWidget();
}

void TeachingDashboardWindow::updateTreeWidget() {
	ui.treeWidget->clear();
	
	//find records in range
	QList<TeachingRecord> recordsInRange = filterByDateRange(records,
													ui.startDateSelector->date(),
													ui.endDateSelector->date());

    //loop all records in rang to modify the startDate
    //                         and to count the value for Hour and numStudent
    QMap<QString, QMap<QString,QMap<QString,double>>> recordsSummaryHour;
    QMap<QString, QMap<QString,QMap<QString,int>>> recordsSummaryStudent;
	for (const TeachingRecord &record : recordsInRange) {
        recordsSummaryHour[record.programType][record.academicYear][record.memberName]+=record.totalhours;
        recordsSummaryStudent[record.programType][record.academicYear][record.memberName]+=record.numStudent;
	}
    
    

    //build the view for recorded within range


    double count_tchH=0;
    int count_tchS=0;
    QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget);
    ui.treeWidget->expandItem(root);
	
    auto progTypeH = recordsSummaryHour.begin();
    auto progTypeS = recordsSummaryStudent.begin();
    //for program level
    while ( (progTypeH != recordsSummaryHour.end()) && (progTypeS!=recordsSummaryStudent.end())){
        QTreeWidgetItem *progNode = new QTreeWidgetItem(root);
        //for key of academicYear
        
        double count_progH=0;
        int count_proS=0;
        
        auto yearH = progTypeH.value().begin();
        auto yearS = progTypeS.value().begin();
        while (yearH != progTypeH.value().end() && yearS != progTypeS.value().end()) {
            QTreeWidgetItem *yearNode =new QTreeWidgetItem(progNode);
            
            double count_yearH=0;
            int count_yearS=0;
            
            //for faculty level
            auto nameH = yearH.value().begin();
            auto nameS = yearS.value().begin();
            while (nameH!=yearH.value().end() && nameS!=yearS.value().end()) {
                QTreeWidgetItem *nameNode= new QTreeWidgetItem(yearNode);
                nameNode->setText(0,nameH.key());//facutly name
                nameNode->setText(1,QString::number(nameH.value()));//hour/faculty
                nameNode->setText(2,QString::number(nameS.value()));//student/faculty
                count_yearH+=nameH.value();//hours/year
                count_yearS+=nameS.value();//students/year
                ++nameH;
                ++nameS;
            }
            yearNode->setText(0,yearH.key());
            yearNode->setText(1,QString::number(count_yearH));
            yearNode->setText(2,QString::number(count_yearS));

            count_progH+=count_yearH;//hour/program
            count_proS+=count_yearS;//student/program
            ++yearH;
            ++yearS;
		}

        progNode->setText(0,progTypeH.key());
        progNode->setText(1,QString::number(count_progH));
        progNode->setText(2,QString::number(count_proS));

        count_tchH+=count_progH;
        count_tchS+=count_proS;

        ++progTypeH;
        ++progTypeS;
	}

    root->setText(0,"Teaching");
    root->setText(1,QString::number(count_tchH));
    root->setText(2,QString::number(count_tchS));


    // for now, make sure that column width is at least equal to contents
    for (int i = 0; i < ui.treeWidget->columnCount(); i++) {
        ui.treeWidget->resizeColumnToContents(i);
    }
}

/*
//Opens a VisualizationWindow if the row that was doubleclicked contains a faculty member
 void PresentationDashboardWindow::on_treeWidget_doubleClicked()
{
    QTreeWidgetItem *header = ui.treeWidget->headerItem();
    int facultyMemberNameColumn = 0;
    for (int i = 0; i < ui.treeWidget->columnCount(); i++) {
        if (header->text(i) == "Faculty Name") {
            facultyMemberNameColumn = i;
        }
    }

    //Gets the row that was doubleclicked; I believe selectedItems() only returns what has keyboard focus, which can only be one row in our case
    //Therefore it should work because it can only ever return the one line that was doubleclicked; still kind of hacky though
    QTreeWidgetItem *selected = ui.treeWidget->selectedItems().first();

    //If the row contains a faculty member name, it's graphable so open a VisualizationWindow
    if(selected->text(facultyMemberNameColumn) != "") {
        VisualizationWindow vw(this);
        QString memberName = selected->text(facultyMemberNameColumn);
        QDate sDate, eDate;
        sDate = ui.startDateSelector->date();
        eDate = ui.endDateSelector->date();
        //vw.init(records, selected->text(facultyMemberNameColumn), ui.startDateSelector->date(), ui.endDateSelector->date());
        vw.init(records, memberName, sDate, eDate);
        vw.exec();
    }

}
*/
