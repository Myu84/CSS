#ifndef PRESENTATION_RECORD_H
#define PRESENTATION_RECORD_H

#include <QString>
#include <QDate>

struct PresentationRecord {
	//required fields
	QString memberName;		//used
	QString primaryDomain;	//used
	QDate date;				//used
	QString type;			//used
	QString role;			//used
	QString title;			//not used (use for next-level)
	
	//optional fields
	QString activityType;
	QString geographicalScope;
	QString host;
	QString country;
	QString province;
	QString city;
	QString numberOfAttendees;
	QString hours;
	QString teachingScore;
	QString educationPresentation;
	QString remarks;
	QString authorship;
	QString restOfCitation;
	QString personalRemuneration;
};

#endif
