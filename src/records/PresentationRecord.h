#ifndef PRESENTATION_RECORD_H
#define PRESENTATION_RECORD_H

#include <QString>
#include <QDate>

struct PresentationRecord {
	QString memberName;
	QString primaryDomain;
	QDate date;
	QString type;
	QString role;
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
	QString title;
	QString restOfCitation;
	QString personalRemuneration;
};

#endif
