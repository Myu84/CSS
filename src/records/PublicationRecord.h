#ifndef PUBLICATION_RECORD_H
#define PUBLICATION_RECORD_H

#include <QString>
#include <QDate>

struct PublicationRecord {
    //required fields
    QString memberName;			//used
    QString primaryDomain;		//used
    QString publicationStatus;	//used
    QString type;				//used
    QDate date;					//used
    QString role;				//used
    QString publishedIn;		//used
    QString authors;			//not used
    QString title;				//used
    
    //optional fields
    QString pubmedID;
    QString peerReviewed;
    QString authorNum;
    QString volume;
    QString issue;
    QString pageRange;
    QString doi;
    QString website;
    QString journalImpactFactor;
    QString international;
    QString publisher;
    QString isPresentation;
    QString remumeration;
    QString traineeDetails;
    QString isMostSignificant;
    QString mostSignificantDetails;
    QString educationPublication;
    QString isbn;
};

#endif
