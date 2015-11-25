#include <QString>
#include <QDate>
#include <QList>
#include <QDebug>
#include <exception>

#include "../records/PublicationRecord.h"
#include "Parser.h"
#include "PublicationParser.h"

using namespace std;

// file_name should be path to file
QList<PublicationRecord> PublicationParser::parse(QString file_name) {
	CSVParser<27> parser(file_name.toStdString());

	parser.read_header(column_policy,
	   "Member Name",
	   "Primary Domain",
	   "Publication Status",
	   "Pubmed Article ID",
	   "Type",
	   "Status Date",
	   "Role",
	   "Peer Reviewed?",
	   "Author #",
	   "Journal Name | Published In | Book Title | etc.",
	   "Volume",
	   "Issue",
	   "Page Range",
	   "DOI",
	   "Website",
	   "Journal Impact Factor",
	   "International",
	   "Publisher",
	   "Is Presentation?",
	   "Personal Remuneration",
	   "Trainee Details",
	   "Is Most Significant Publication?",
	   "Most Significant Contribution Details",
	   "Education Publication",
	   "Author(s)",
	   "Title",
	   "ISBNISSN");

	QList<PublicationRecord> records;
    int lineNum = 1;
	
    while (true) {
		lineNum++;
		
		PublicationRecord curr_record;

		//strings to be converted
		QString curr_date;
		
		bool continueParsing;
		try {
			continueParsing = parser.read_row(curr_record.memberName,
                           curr_record.primaryDomain,
                           curr_record.publicationStatus,
                           curr_record.pubmedID,
                           curr_record.type,
                           curr_date,
                           curr_record.role,
                           curr_record.peerReviewed,
                           curr_record.authorNum,
                           curr_record.publishedIn,
                           curr_record.volume,
                           curr_record.issue,
                           curr_record.pageRange,
                           curr_record.doi,
                           curr_record.website,
                           curr_record.journalImpactFactor,
                           curr_record.international,
                           curr_record.publisher,
                           curr_record.isPresentation,
                           curr_record.remumeration,
                           curr_record.traineeDetails,
                           curr_record.isMostSignificant,
                           curr_record.mostSignificantDetails,
                           curr_record.educationPublication,
                           curr_record.authors,
                           curr_record.title,
                           curr_record.isbn);
        } catch (const std::exception &e) {
			qDebug() << e.what();
			continue;
		}
		
		if (!continueParsing) {
			break;
		}
		
        //validate memberName
        if (curr_record.memberName.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing member name on line " << lineNum;
            continue;
        }

        //validate primaryDomain
        if (curr_record.primaryDomain.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing primary domain on line " << lineNum;
            continue;
        }

        //validate publicationStatus
        if (curr_record.publicationStatus.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing publication Status  on line " << lineNum;
            continue;
        }
        //validate publication type
        if (curr_record.type.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing publication type  on line " << lineNum;
            continue;
        }

        //validate date
		curr_record.date = parseDate(curr_date);
		if (!curr_record.date.isValid()) {
			//TODO: handle error
			qDebug() << "Invalid date: " << curr_date << " on line " << lineNum;
			continue;
		}

        //validate role
        if (curr_record.role.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing role on line " << lineNum;
            continue;
        }

        //validate publishedIn
        if (curr_record.publishedIn.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing published Infomation on line " << lineNum;
            continue;
        }
		
        //validate author
        if (curr_record.authors.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing authors on line " << lineNum;
            continue;
        }

        //validate title
        if (curr_record.title.isEmpty()) {
            //TODO: handle error
            qDebug() << "Missing title on line " << lineNum;
            continue;
        }

        records.append(curr_record);
	}

	return records;
}
