#include <QString>
#include <QDate>
#include <QList>
#include <QDebug>

#include "../records/GrantRecord.h"
#include "Parser.h"
#include "GrantParser.h"

using namespace std;

// file_name should be path to file
QList<GrantRecord> GrantParser::parse(QString file_name) {
	CSVParser<32> parser(file_name.toStdString());

	parser.read_header(column_policy,
                       "Member Name",
                       "Primary Domain",
                       "Start Date",
                       "End Date",
                       "Funding Type",
                       "Status",
                       "Peer Reviewed?",
                       "Industry Grant?",
                       "Role",
                       "Short Title",
                       "Title",
                       "Application Summary",
                       "Grant Purpose",
                       "Area",
                       "Principal Investigator",
                       "Co-Investigators",
                       "Grant and/or Account #",
                       "Prorated Amount",
                       "Administered By",
                       "Funding Source",
                       "Project",
                       "Currency",
                       "Received Amount",
                       "Total Amount",
                       "Member Share",
                       "Monetary",
                       "Rpt",
                       "Hours Per Week",
                       "Personnel Paid",
                       "Rnw",
                       "Education Grant",
                       "Duplicate Reported");
	
	QList<GrantRecord> records;
	
	GrantRecord curr_record;
	
    //strings to be converted
    QString curr_startDate;
    QString curr_endDate;
    QString curr_peerReviewed;
    QString curr_industryGrant;
    QString curr_totalAmount;

    
    int lineNum = 1;
    while (parser.read_row(curr_record.memberName,
                           curr_record.primaryDomain,
                           curr_startDate,
                           curr_endDate,
                           curr_record.fundingType,
                           curr_record.status,
                           curr_peerReviewed,
                           curr_industryGrant,
                           curr_record.role,
                           curr_record.title,
                           curr_record.principalInvestigator,
                           curr_record.coInvestigators,
                           curr_totalAmount,
                           curr_record.shortTitle,
                           curr_record.applicationSummary,
                           curr_record.grantPurpose,
						   curr_record.area,
						   curr_record.grantNumber,
						   curr_record.proratedAmount,
						   curr_record.administeredBy,
                           curr_record.fundingSource,
                           curr_record.project,
                           curr_record.currency,
                           curr_record.receivedAmount,
                           curr_record.memberShare,
                           curr_record.monetary,
                           curr_record.reportable,
                           curr_record.hoursPerWeek,
                           curr_record.personnelPaid,
                           curr_record.rnw,
                           curr_record.educationGrant,
                           curr_record.duplicateReported)) {
		bool parseOK;
        lineNum++;
		
        //validate memberName
        if (curr_record.memberName.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing member name on line " << lineNum;
            continue;
        }
        
        //validate primaryDomain
        if (curr_record.primaryDomain.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing primary domain on line " << lineNum;
            continue;
        }
        
        //validate startDate
		curr_record.startDate = parseDate(curr_startDate);
		if (!curr_record.startDate.isValid()) {
			//TODO: handle error
			qDebug() << "Invalid start date: " << curr_startDate << " on line " << lineNum;
			continue;
		}
		
		//validate endDate
		curr_record.endDate = parseDate(curr_endDate);
		if (!curr_record.endDate.isValid()) {
			//TODO: handle error
			qDebug() << "Invalid end date: " << curr_endDate << " on line " << lineNum;
			continue;
		}
		
		//validate date range
		if (curr_record.startDate > curr_record.endDate) {
			//TODO: handle error
			qDebug() << "Start date after end date on line " << lineNum;
			continue;
		}
        
		//validate program
        if (curr_record.fundingType.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing funding type on line " << lineNum;
            continue;
        }
		
		//validate activityType
        if (curr_record.status.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing status on line " << lineNum;
            continue;
        }
        
        
        //validate peerRevied
        if (curr_peerReviewed.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing peer review info on line " << lineNum;
            continue;
        }
        else

        
        
        //validate industryGrant
        if (curr_industryGrant.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing industry grant info on line " << lineNum;
            continue;
        }
        
        //validate that there is either peerReviewed or industryGrant but not both
        if(curr_peerReviewed=="TRUE"){
            if(curr_industryGrant=="TRUE"){
                qDebug() << "Peer reviewed and industry grant both true on line " << lineNum;
                continue;
            }
            else
                curr_record.fundingPurpose="Peer Reviewed";
        }
        else{
            if(curr_industryGrant=="FALSE"){
                qDebug() << "Peer reviewed and industry grant both false on line " << lineNum;
                continue;
            }
            else
                curr_record.fundingPurpose="Industry Sponsored";
        }
        
        //validate role
        if (curr_record.role.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing role on line " << lineNum;
            continue;
        }
        
        //validate title
        if (curr_record.title.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing title on line " << lineNum;
            continue;
        }
        
        //validate principalInvestigator
        if (curr_record.principalInvestigator.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing principalInvestigator on line " << lineNum;
            continue;
        }
        
        //validate coInvestigators
        if (curr_record.coInvestigators.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing coInvestigators on line " << lineNum;
            continue;
        }
        
        
        //validate totalAmount
		curr_record.totalAmount = curr_totalAmount.toDouble(&parseOK);
        if (!parseOK || curr_record.totalAmount< 0) {
            //TODO: handle error
            qDebug() << "Invalid total amount on line " << lineNum;
            continue;
        }
        
		records.append(curr_record);
	}
	
	return records;
}
