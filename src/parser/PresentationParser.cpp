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
	
	//strings to be converted
	QString curr_date;
	
    int lineNum = 1;
	while (parser.read_row(curr_record.memberName, 
						   curr_record.primaryDomain, 
						   curr_date, 
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
		lineNum++;
		
		//validate date
		curr_record.date = parseDate(curr_date);
		if (!curr_record.date.isValid()) {
			//TODO: handle error
			qDebug() << "Invalid date: " << curr_date << " on line " << lineNum;
			continue;
		}
		
		//validate memberName
		if (curr_record.memberName.isEmpty()) {
			//TODO: handle error
			qDebug() << "Missing member name on line " << lineNum;
			continue;
		}
		
		//validate type
		if (curr_record.type.isEmpty()) {
			//TODO: handle error
			qDebug() << "Missing type on line " << lineNum;
			continue;
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
		
		records.append(curr_record);
	}
	
	return records;
}
