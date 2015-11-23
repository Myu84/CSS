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
    QDate starusDate;
    QString role;
    QString publishedIn;
    QString author;
    QString title;
    
    //optional fields
    QString pubmedID;
    QString area;
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
    QString remunation;
    QString details;
    QString significance;
    QString educationPublic;
    QString ISB;
};

#endif
