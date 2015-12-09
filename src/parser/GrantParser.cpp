#include <QString>
#include <QDate>
#include <QList>
#include <QTextStream>
#include <exception>

#include "../records/GrantRecord.h"
#include "Parser.h"
#include "GrantParser.h"

using namespace std;

// file_name should be path to file
QList<GrantRecord> GrantParser::parse(const QString &file_name) {
	CSVParser<31> parser(file_name.toStdString());

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
    int lineNum = 1;
	
	QString errorLog;
	QTextStream errorStream(&errorLog);
	
	int numErrors = 0;
	int numWarnings = 0;
	
    while (true) {
		lineNum++;
		
		GrantRecord curr_record;
	
		//strings to be converted
		QString curr_startDate;
		QString curr_endDate;
		QString curr_peerReviewed;
		QString curr_industryGrant;
		QString curr_totalAmount;
	
		bool continueParsing;
		try {
			continueParsing = parser.read_row(curr_record.memberName,
                           curr_record.primaryDomain,
                           curr_startDate,
                           curr_endDate,
                           curr_record.fundingType,
                           curr_record.status,
                           curr_peerReviewed,
                           curr_industryGrant,
                           curr_record.role,
                           curr_record.shortTitle,
                           curr_record.title,
                           curr_record.applicationSummary,
                           curr_record.grantPurpose,
						   curr_record.area,
						   curr_record.principalInvestigator,
						   curr_record.coInvestigators,
						   curr_record.grantNumber,
						   curr_record.administeredBy,
                           curr_record.fundingSource,
                           curr_record.project,
                           curr_record.currency,
                           curr_record.receivedAmount,
                           curr_totalAmount,
                           curr_record.memberShare,
                           curr_record.monetary,
                           curr_record.reportable,
                           curr_record.hoursPerWeek,
                           curr_record.personnelPaid,
                           curr_record.rnw,
                           curr_record.educationGrant,
                           curr_record.duplicateReported);
		} catch (const std::exception &e) {
			errorStream << "Error: Parser error: " << e.what() << " on line " << lineNum << "\n";
			numErrors++;
			continue;
		}
		
		if (!continueParsing) {
			break;
		}
		
		bool parseOK;
		
        //validate memberName
        if (curr_record.memberName.isEmpty()) {
            errorStream << "Error: Missing member name on line " << lineNum << "\n";
			numErrors++;
            continue;
        }
        
        //validate primaryDomain
        if (curr_record.primaryDomain.isEmpty()) {
            errorStream << "Error: Missing primary domain on line " << lineNum << "\n";
			numErrors++;
            continue;
        }
        
        //validate startDate
		curr_record.startDate = parseDate(curr_startDate);
		if (!curr_record.startDate.isValid()) {
			errorStream << "Error: Invalid start date '" << curr_startDate << "' on line " << lineNum << "\n";
			numErrors++;
			continue;
		}
		
		//validate endDate
		curr_record.endDate = parseDate(curr_endDate);
		if (!curr_record.endDate.isValid()) {
			errorStream << "Error: Invalid end date '" << curr_endDate << "' on line " << lineNum << "\n";
			numErrors++;
			continue;
		}
		
		//validate date range
		if (curr_record.startDate > curr_record.endDate) {
			errorStream << "Error: Start date is later than end date on line " << lineNum << "\n";
			numErrors++;
			continue;
		}
        
		//validate fundingType
        if (curr_record.fundingType.isEmpty()) {
            errorStream << "Error: Missing funding type on line " << lineNum << "\n";
            numErrors++;
			continue;
        }
		
		//validate status
        if (curr_record.status.isEmpty()) {
            errorStream << "Warning: Missing status on line " << lineNum << "\n";
            numWarnings++;
        }
        
        //validate peerReviewed
        curr_record.peerReviewed = parseBool(curr_peerReviewed, &parseOK);
		if (!parseOK) {
			errorStream << "Error: Invalid value '" << curr_peerReviewed << "' for 'Peer Reviewed?' column on line " << lineNum << "\n";
			numErrors++;
			continue;
		}

        //validate industryGrant
        curr_record.industryGrant = parseBool(curr_industryGrant, &parseOK);
		if (!parseOK) {
			errorStream << "Error: Invalid value '" << curr_industryGrant << "' for 'Industry Grant?' column on line " << lineNum << "\n";
			numErrors++;
			continue;
		}
        
        //validate role
        if (curr_record.role.isEmpty()) {
            errorStream << "Warning: Missing role on line " << lineNum << "\n";
            numWarnings++;
        }
        
        //validate title
        if (curr_record.title.isEmpty()) {
            errorStream << "Error: Missing title on line " << lineNum << "\n";
            numErrors++;
			continue;
        }
        
        //validate principalInvestigator
        if (curr_record.principalInvestigator.isEmpty()) {
            errorStream << "Warning: Missing principal investigator on line " << lineNum << "\n";
            numWarnings++;
        }
        
        //validate coInvestigators
        if (curr_record.coInvestigators.isEmpty()) {
            errorStream << "Warning: Missing co-investigators on line " << lineNum << "\n";
            numWarnings++;
        }
        
        //validate totalAmount
		curr_record.totalAmount = parseMoney(curr_totalAmount, &parseOK);
        if (!parseOK) {
            errorStream << "Error: Invalid total amount '" << curr_totalAmount << "' on line " << lineNum << "\n";
			numErrors++;
            continue;
        }
        
		records.append(curr_record);
	}
	
	return records;
}
