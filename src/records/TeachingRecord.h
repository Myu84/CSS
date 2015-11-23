#ifndef TEACHING_RECORD_H
#define TEACHING_RECORD_H

#include <QtGlobal>
#include <QString>
#include <QDate>

struct TeachingRecord {
	//required fields
    QString memberName;
    QString primaryDomain;
    QDate startDate;
    QDate endDate;
    QString program;
    QString activityType;
	QString geographicalScope;
	double hoursPerSession;
	double numberOfSessions;
	double totalHours;
	
	//optional fields
	uint numTrainees;
	QString activity;
    QString institution;
    QString faculty;
    QString department;
    QString division;
    QString location;
    QString additionalComments;
    QString studentNames;
    QString initialLecture;
    QString facultyDevelopment;
    QString comment;
};

#endif
