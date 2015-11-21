#ifndef TEACHING_RECORD_H
#define TEACHING_RECORD_H

#include <QString>
#include <QDate>
#include <QPair>

struct TeachingRecord {
	

   
    QString memberName;
    QString primaryDomain;
    QString academicYear;
    QDate date;
    QString programType;
    /*
     1. PME: Postgraduate Medical Education
     2. UME: Undergraduate Medical Education
     3. CME: Continuing Medical Education
     4. Other
    */
    
    QString activityType;
    QString geographicalScope;
    QString hoursPerSession;//wont be used
    double  totalhours;
    int numStudent;
};

#endif
