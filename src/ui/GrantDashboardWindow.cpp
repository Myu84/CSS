#include <cstdlib>
#include <exception>
#include <QtGlobal>
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QPair>
#include <QDebug>
#include <QTreeWidgetItem>

#include "GrantDashboardWindow.h"
#include "../records/GrantRecord.h"
#include "../parser/GrantParser.h"
#include "UIUtils.h"
#include "VisualizationWindow.h"

static const int facultyMemberNameColumn = 3;

QString grantDescription(bool peerReviewed, bool industryGrant) {
	if (peerReviewed && industryGrant) {
		return "Peer Reviewed Industry Grant";
	} else if (peerReviewed) {
		return "Peer Reviewed";
	} else if (industryGrant) {
		return "Industry Grant";
	} else {
		return "Other";
	}
}

QString moneyToStr(double amount) {
	return "$" + QString::number(amount, 'f', 2);
}

GrantDashboardWindow::GrantDashboardWindow(QString csv_filename) {
	GrantParser parser;
	
	try {
		records = parser.parse(csv_filename);
	} catch (const std::exception &e) {
		qDebug() << e.what();
		QMessageBox::critical(this, "Error", "A fatal error occurred while parsing the CSV file");
		exit(1);
	}
	
	if (records.empty()) {
		QMessageBox::critical(this, "Error", "The CSV file has no records");
		exit(1);
	}
	
	ui.treeWidget->setHeaderLabels(QStringList() << 
						"" << "Funding Type" << "Funding Description" << "Faculty Name" << "Total #" << "Total $");
	
	ui.subjectAreaLabel->setText("Grant/Funding Summary");
	ui.departmentLabel->setText("Department of " + records[0].primaryDomain);
	ui.statusbar->showMessage("Read " + QString::number(records.size()) + " records from " + csv_filename);
    setWindowTitle("Grant - " + records[0].primaryDomain + " - " + csv_filename);
	
	QPair<QDate, QDate> dateInterval = findDateRangeStartEnd(records);
	ui.startDateSelector->setDate(dateInterval.first);
	ui.endDateSelector->setDate(dateInterval.second);
	
	updateDateLabel();
	updateTreeWidget();
}

void GrantDashboardWindow::updateTreeWidget() {
	ui.treeWidget->clear();
	
	//find records in range
    QList<GrantRecord> recordsInRange = filterByDateRangeStartEnd(records,
											ui.startDateSelector->date(),
											ui.endDateSelector->date());

    //total the records
    QPair<int, double> allSummary;
    QMap<QString, QPair<int, double>> typeSummary;
    QMap<QString, QMap<QString, QPair<int, double>>> descSummary;
    QMap<QString, QMap<QString, QMap<QString, QPair<int, double>>>> nameSummary;

	for (const GrantRecord &record : recordsInRange) {
		QString desc = grantDescription(record.peerReviewed, record.industryGrant);
		
		++allSummary.first;
        allSummary.second += record.totalAmount;
		
        ++typeSummary[record.fundingType].first;
        typeSummary[record.fundingType].second += record.totalAmount;
        
        ++descSummary[record.fundingType][desc].first;
        descSummary[record.fundingType][desc].second += record.totalAmount;
		
        ++nameSummary[record.fundingType][desc][record.memberName].first;
        nameSummary[record.fundingType][desc][record.memberName].second += record.totalAmount;
	}

    //build the view
    QTreeWidgetItem *root = new QTreeWidgetItem(ui.treeWidget, (QStringList() << 
                                    "Grants and Clinical Funding" << "" << "" << "" << QString::number(allSummary.first) << moneyToStr(allSummary.second)));
	ui.treeWidget->expandItem(root);
	
    for (auto type = typeSummary.begin(); type != typeSummary.end(); ++type) {
        QTreeWidgetItem *typeNode = new QTreeWidgetItem(root, (QStringList() <<
                                            "" << type.key() << "" << "" << QString::number(type.value().first) << moneyToStr(type.value().second)));
		
        QMap<QString, QPair<int, double>> &currDescSummary = descSummary[type.key()];
        for (auto desc = currDescSummary.begin(); desc != currDescSummary.end(); ++desc) {
            QTreeWidgetItem *descNode = new QTreeWidgetItem(typeNode, (QStringList() <<
                                                "" << "" << desc.key() << "" << QString::number(desc.value().first) << moneyToStr(desc.value().second)));
		
            QMap<QString, QPair<int, double>> &currNameSummary = nameSummary[type.key()][desc.key()];
			for (auto name = currNameSummary.begin(); name != currNameSummary.end(); ++name) {
                new QTreeWidgetItem(descNode, (QStringList() <<
						"" << "" << "" << name.key() << QString::number(name.value().first) << moneyToStr(name.value().second)));
			}
		}
	}

	setColumnWidths();
}


//Opens a VisualizationWindow if the row that was doubleclicked contains a faculty member
void GrantDashboardWindow::on_treeWidget_doubleClicked() {
	/*
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
    */
}
