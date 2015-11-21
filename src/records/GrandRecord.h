#ifndef GRAND_RECORD_H
#define GRAND_RECORD_H

#include <QString>
#include <QDate>

struct GrandRecord {
	

   
    QString memberName;
    QString primaryDomain;
    QDate startDate;
    QDate endDate;
    QString fundingType;
    QString status;
    bool peerReviewed;
    bool industryGrant;
    QString Role;
    QString title;
    QString principalInvestigator;
    QString coInvestigators;
    int totalAmount;

};

#endif
