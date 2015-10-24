#include <QString>
#include <QDate>
#include <QList>
#include <QDebug>
#include <string>

#include "../records/PresentationRecord.h"
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
	
	std::string memberName, primaryDomain, date, type, role, activityType, 
				geographicalScope, host, country, province, city, 
				numberOfAttendees, hours, teachingScore, educationPresentation,
				remarks, authorship, title, restOfCitation, personalRemuneration;
	
	while (parser.read_row(memberName, primaryDomain, date, type, role, 
						   activityType, geographicalScope, host, country, province, 
						   city, numberOfAttendees, hours, teachingScore, 
						   educationPresentation, remarks, authorship, title, 
						   restOfCitation, personalRemuneration)) {
		PresentationRecord curr_record;
		
		curr_record.memberName = QString::fromStdString(memberName);
		curr_record.primaryDomain = QString::fromStdString(primaryDomain);
		curr_record.type = QString::fromStdString(type);
		curr_record.role = QString::fromStdString(role);
		curr_record.activityType = QString::fromStdString(activityType);
		curr_record.geographicalScope = QString::fromStdString(geographicalScope);
		curr_record.host = QString::fromStdString(host);
		curr_record.country = QString::fromStdString(country);
		curr_record.province = QString::fromStdString(province);
		curr_record.city = QString::fromStdString(city);
		curr_record.numberOfAttendees = QString::fromStdString(numberOfAttendees);
		curr_record.hours = QString::fromStdString(hours);
		curr_record.teachingScore = QString::fromStdString(teachingScore);
		curr_record.educationPresentation = QString::fromStdString(educationPresentation);
		curr_record.remarks = QString::fromStdString(remarks);
		curr_record.authorship = QString::fromStdString(authorship);
		curr_record.title = QString::fromStdString(title);
		curr_record.restOfCitation = QString::fromStdString(restOfCitation);
		curr_record.personalRemuneration = QString::fromStdString(personalRemuneration);
		
		QString q_datestr = QString::fromStdString(date);
		curr_record.date = QDate::fromString(q_datestr, "yyyy/M/d");
		if (!curr_record.date.isValid()) {
			curr_record.date = QDate::fromString(q_datestr, "yyyy/M");
			if (!curr_record.date.isValid()) {
				curr_record.date = QDate::fromString(q_datestr, "yyyy");
				if (!curr_record.date.isValid()) {
					//TODO: handle invalid date entry
					qDebug() << "Invalid date entry: " << curr_record.memberName << " " << q_datestr;
					continue;
				}
			}
		}
		
		/*
			Error checking goes here
		*/
		
		records.append(curr_record);
	}
	
	return records;
}
