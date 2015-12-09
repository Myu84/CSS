#ifndef TEACHING_RECORD_H
#define TEACHING_RECORD_H

#include <QtGlobal>
#include <QString>
#include <QDate>

struct TeachingRecord {
	//required fields
    QString memberName;		//used
    QString primaryDomain;	//used
    QDate startDate;		//used
    QDate endDate;			//used
    QString program;		//used
    QString activityType;	//used (use for next-level)
	QString geographicalScope; //not used
	double hoursPerSession; //not used
	double numberOfSessions;//not used
	double totalHours;		//used
	
	//optional fields
	uint numTrainees;		//used
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
