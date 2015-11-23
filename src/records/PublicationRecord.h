#ifndef PUBLICATION_RECORD_H
#define PUBLICATION_RECORD_H

#include <QString>
#include <QDate>

struct PublicationRecord {
    //required fields
    QString memberName;
    QString primaryDomain;
    QString publicationStatus;
    QString type;
    QDate date;
    QString role;
    QString publishedIn;
    QString authors;
    QString title;
    
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
