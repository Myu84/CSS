#ifndef GRANT_RECORD_H
#define GRANT_RECORD_H

#include <QString>
#include <QDate>

struct GrantRecord {
	//required fields
    QString memberName;		//used
    QString primaryDomain;	//used
    QDate startDate;		//used
    QDate endDate;			//used
    QString fundingType;	//used
    QString status;			//not used
    bool peerReviewed;		//used
    bool industryGrant;		//used
    QString role;			//not used
	QString title;			//not used (use for next-level)
	QString principalInvestigator; //not used
    QString coInvestigators;//not used
	double totalAmount;		//used
	
	//optional fields
    QString shortTitle;
    QString applicationSummary;
    QString grantPurpose;
    QString area;
    QString grantNumber;
	QString administeredBy;
	QString fundingSource;
	QString project;
	QString currency;
    QString receivedAmount;
    QString memberShare;
	QString monetary;
	QString reportable;
	QString hoursPerWeek;
	QString personnelPaid;
	QString rnw;
	QString educationGrant;
	QString duplicateReported;
};

#endif
