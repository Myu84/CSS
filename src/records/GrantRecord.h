#ifndef GRANT_RECORD_H
#define GRANT_RECORD_H

#include <QString>
#include <QDate>

struct GrantRecord {
	//required fields
    QString memberName;
    QString primaryDomain;
    QDate startDate;
    QDate endDate;
    QString fundingType;
    QString status;
    bool peerReviewed;
    bool industryGrant;
    QString role;
	QString title;
	QString principalInvestigator;
    QString coInvestigators;
	double totalAmount;
	
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
