#include <QString>
#include <QDate>
#include <QList>
#include <QTextStream>
#include <exception>

#include "../records/TeachingRecord.h"
#include "Parser.h"
#include "TeachingParser.h"

using namespace std;

// file_name should be path to file
QList<TeachingRecord> TeachingParser::parse(const QString &file_name) {
	CSVParser<22> parser(file_name.toStdString());

	parser.read_header(column_policy,
        "Member Name",
		"Primary Domain",
		"Start Date",
		"End Date",
		"Program",
		"Type of Course / Activity",
		"Course / Activity",
		"Geographical Scope",
		"Institution / Organization",
		"Faculty",
		"Department",
		"Division",
		"Location",
		"Hours per Teaching Session or Week",
		"Number of Teaching Sessions or Weeks",
		"Faculty Member Additional Comments",
		"Number Of Trainees",
		"Student Name(s)",
		"Initial Lecture",
		"Faculty Development",
		"Comment",
		"Total Hours");
	
	QList<TeachingRecord> records;
	int lineNum = 1;
	
	QString errorLog;
	QTextStream errorStream(&errorLog);
	
	int numErrors = 0;
	int numWarnings = 0;
	
    while (true) {
		lineNum++;
		
		TeachingRecord curr_record;
	
		//strings to be converted
		QString curr_startDate;
		QString curr_endDate;
		QString curr_hoursPerSession;
		QString curr_numberOfSessions;
		QString curr_numTrainees;
		QString curr_totalHours;
		
		bool continueParsing;
		try {
			continueParsing = parser.read_row(curr_record.memberName,
                           curr_record.primaryDomain,
                           curr_startDate,
                           curr_endDate,
                           curr_record.program,
                           curr_record.activityType,
                           curr_record.activity,
                           curr_record.geographicalScope,
                           curr_record.institution,
                           curr_record.faculty,
                           curr_record.department,
                           curr_record.division,
                           curr_record.location,
                           curr_hoursPerSession,
                           curr_numberOfSessions,
						   curr_record.additionalComments,
                           curr_numTrainees,
						   curr_record.studentNames,
						   curr_record.initialLecture,
						   curr_record.facultyDevelopment,
                           curr_record.comment,
						   curr_totalHours);
		} catch (const std::exception &e) {
			errorStream << "Error: Parser error: " << e.what() << " on line " << lineNum;
			numErrors++;
			continue;
		}
		
		if (!continueParsing) {
			break;
		}
		
		bool parseOK;
		
        //validate memberName
        if (curr_record.memberName.isEmpty()) {
            errorStream << "Error: Missing member name on line " << lineNum;
			numErrors++;
            continue;
        }

        //validate primaryDomain
        if (curr_record.primaryDomain.isEmpty()) {
            errorStream << "Error: Missing primary domain on line " << lineNum;
			numErrors++;
            continue;
        }
        
        //validate startDate
		curr_record.startDate = parseDate(curr_startDate);
		if (!curr_record.startDate.isValid()) {
			errorStream << "Error: Invalid start date '" << curr_startDate << "' on line " << lineNum;
			numErrors++;
			continue;
		}
		
		//validate endDate
		curr_record.endDate = parseDate(curr_endDate);
		if (!curr_record.endDate.isValid()) {
			errorStream << "Error: Invalid end date '" << curr_endDate << "' on line " << lineNum;
			numErrors++;
			continue;
		}
		
		//validate date range
		if (curr_record.startDate > curr_record.endDate) {
			errorStream << "Error: Start date is later than end date on line " << lineNum;
			numErrors++;
			continue;
		}
        
		//validate program
        if (curr_record.program.isEmpty()) {
            errorStream << "Error: Missing program on line " << lineNum;
			numErrors++;
            continue;
        }
		
		//validate activityType
        if (curr_record.activityType.isEmpty()) {
            errorStream << "Error: Missing activity type on line " << lineNum;
			numErrors++;
            continue;
        }
        
        //validate geographicalScope
        if (curr_record.geographicalScope.isEmpty()) {
            errorStream << "Warning: Missing grographical scope on line " << lineNum;
            numWarnings++;
        }
        
        //validate hoursPerSession
		curr_record.hoursPerSession = curr_hoursPerSession.toDouble(&parseOK);
        if (!parseOK || curr_record.hoursPerSession < 0) {
            errorStream << "Warning: Invalid hours per session '" << curr_hoursPerSession << "' on line " << lineNum;
            numWarnings++;
        }

        //validate numberOfSessions
		curr_record.numberOfSessions = curr_numberOfSessions.toDouble(&parseOK);
        if (!parseOK || curr_record.numberOfSessions < 0) {
            errorStream << "Warning: Invalid number of sessions '" << curr_numberOfSessions << "' on line " << lineNum;
            numWarnings++;
        }
		
		//validate totalHours
		curr_record.totalHours = curr_totalHours.toDouble(&parseOK);
        if (!parseOK || curr_record.totalHours < 0) {
            errorStream << "Warning: Invalid total hours '" << curr_totalHours << "' on line " << lineNum;
            numErrors++;
			continue;
        }
		
		//validate numTrainees
		curr_record.numTrainees = curr_numTrainees.toUInt(&parseOK);
        if (!parseOK) {
			curr_record.numTrainees = 0;
            errorStream << "Warning: Invalid number of trainees '" << curr_numTrainees << "' on line " << lineNum;
            numWarnings++;
        }
		
		records.append(curr_record);
	}
	
	return records;
}
