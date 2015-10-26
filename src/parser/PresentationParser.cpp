#include <QString>
#include <QDate>
#include <QList>
#include <QDebug>

#include "../records/PresentationRecord.h"
#include "Parser.h"
#include "PresentationParser.h"

using namespace std;

// file_name should be path to file
QList<PresentationRecord> PresentationParser::parse(QString file_name) {
	CSVParser<20> parser(file_name.toStdString());

	parser.read_header(column_policy,
		"Member Name",
		"Primary Domain",
		"Date",
		"Type",
		"Role",
		"Activity Type",
		"Geographical Scope",
		"Host",
		"Country",
		"Province",
		"City",
		"Number of Attendees",
		"Hours",
		"Teaching Effectiveness Score",
		"Education Presentation",
		"Remarks",
		"Authorship",
		"Title",
		"Rest of Citation",
		"Personal Remuneration");
	
	QList<PresentationRecord> records;
	
	PresentationRecord curr_record;
	QString curr_datestr;
	
    int count = 2; // keep track of csv line being read. Start at 2 to account for the header
	while (parser.read_row(curr_record.memberName, 
						   curr_record.primaryDomain, 
						   curr_datestr, 
						   curr_record.type, 
						   curr_record.role, 
						   curr_record.activityType, 
						   curr_record.geographicalScope, 
						   curr_record.host, 
						   curr_record.country, 
						   curr_record.province, 
						   curr_record.city, 
						   curr_record.numberOfAttendees, 
						   curr_record.hours, 
						   curr_record.teachingScore, 
						   curr_record.educationPresentation, 
						   curr_record.remarks, 
						   curr_record.authorship, 
						   curr_record.title, 
						   curr_record.restOfCitation, 
						   curr_record.personalRemuneration)) {
		//validate date entry
		curr_record.date = QDate::fromString(curr_datestr, "yyyy/M/d");
		if (!curr_record.date.isValid()) {
			curr_record.date = QDate::fromString(curr_datestr, "yyyy/M");
			if (!curr_record.date.isValid()) {
				curr_record.date = QDate::fromString(curr_datestr, "yyyy");
				if (!curr_record.date.isValid()) {
					//TODO: handle invalid date entry
                    qDebug() << "Invalid date entry: " << curr_datestr << " on line " << count;
					continue;
				}
			}
		}
		
		//validate name
		if (curr_record.memberName.isEmpty()) {
			//TODO: handle missing name
			qDebug() << "Missing member name on line " << count;
			continue;
		}
		
		//validate type
		if (curr_record.type.isEmpty()) {
			//TODO: handle missing type
			qDebug() << "Missing type on line " << count;
			continue;
		}
		
		//validate title
		if (curr_record.title.isEmpty()) {
			//TODO: handle missing title
			qDebug() << "Missing title on line " << count;
			continue;
		}
		
		records.append(curr_record);
        ++count;
	}
	
	return records;
}
