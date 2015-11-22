#include <QString>
#include <QDate>
#include <QList>
#include <QDebug>

#include "../records/PublicationRecord.h"
#include "Parser.h"
#include "PublicationParser.h"

using namespace std;

// file_name should be path to file
QList<PublicationRecord> PublicationParser::parse(QString file_name) {
	CSVParser<28> parser(file_name.toStdString());

	parser.read_header(column_policy,
                       "Member Name",
                       "Primary Domain",
                       "Publication Status",
                       "Pubmed Article ID",
                       "Type",
                       "Area",
                       "Status Date",
                       "Role",
                       "Peer Reviewed?",
                       "Author #",
                       "Journal Name | Published In | Book Title | etc.",
                       "Volume",
                       "Issue",
                       "Page Range",
                       "DOI",
                       "Website",
                       "Journal Impact Factor",
                       "International",
                       "Publisher",
                       "Is Presentation?",
                       "Personal Remuneration",
                       "Trainee Details",
                       "Is Most Significant Publication?",
                       "Most Significant Contribution Details",
                       "Education Publication",
                       "Author(s)",
                       "Title",
                       "ISBNISSN");
	
	QList<GrantRecord> records;
	
	TeachingRecord curr_record;
	
    //strings to be converted
    QString curr_date;
    QString curr_hoursPerSession;
    QString curr_numberOfSessions;
    QString curr_numTrainees;
    QString curr_totalHours;
    
    int lineNum = 1;
    while (parser.read_row(curr_record.memberName,
                           curr_record.primaryDomain,
                           curr_record.publicationStatus,
                           curr_record.type,
                           curr_date,
                           curr_record.role,
                           curr_record.publishedIn,
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
						   curr_totalHours)) {
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
        if (curr_record.program.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing program on line " << lineNum;
            continue;
        }
		
		//validate activityType
        if (curr_record.activityType.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing activity type on line " << lineNum;
            continue;
        }
        
		//geographicalScope is missing too often to check
		/*
        //validate geographicalScope
        if (curr_record.geographicalScope.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing geographical scope on line " << lineNum;
            continue;
        }
		*/
        
        //validate hoursPerSession
		curr_record.hoursPerSession = curr_hoursPerSession.toDouble(&parseOK);
        if (!parseOK || curr_record.hoursPerSession < 0) {
            //TODO: handle error
            qDebug() << "Invalid hours per session on line " << lineNum;
            continue;
        }

        //validate numberOfSessions
		curr_record.numberOfSessions = curr_numberOfSessions.toDouble(&parseOK);
        if (!parseOK || curr_record.numberOfSessions < 0) {
            //TODO: handle error
            qDebug() << "Invalid number of sessions on line " << lineNum;
            continue;
        }
		
		//validate totalHours
		curr_record.totalHours = curr_totalHours.toDouble(&parseOK);
        if (!parseOK || curr_record.totalHours < 0) {
            //TODO: handle error
            qDebug() << "Invalid total hours on line " << lineNum;
            continue;
        }
		
		//validate numTrainees
		curr_record.numTrainees = curr_numTrainees.toUInt(&parseOK);
        if (!parseOK) {
            //TODO: handle warning
            qDebug() << "Invalid number of trainees on line " << lineNum;
        }
		
		records.append(curr_record);
	}
	
	return records;
}
