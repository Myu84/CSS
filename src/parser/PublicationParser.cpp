#include <QString>
#include <QDate>
#include <QList>
#include <QTextStream>
#include <exception>

#include "../records/PublicationRecord.h"
#include "Parser.h"
#include "PublicationParser.h"
#include "../ui/ErrorListDialog.h"

using namespace std;

//workaround for strange header in publications sample
Parser::CSVParser<27> *makePublicationParser(const QString &file_name) {
	Parser::CSVParser<27> *parser = nullptr;
	
	try {
		parser = new Parser::CSVParser<27>(file_name.toStdString());

		parser->read_header(Parser::column_policy,
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
		   
		return parser;
	} catch (...) {
		if (parser) {
			delete parser;
		}
		parser = new Parser::CSVParser<27>(file_name.toStdString());

		parser->read_header(Parser::column_policy,
		   "Member Name",
		   "Primary Domain",
		   "Publication Status",
		   "Pubmed Article ID",
		   "Type",
		   "Status Date *", //strange column header
		   "Role *",		//strange column header
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
		   
		return parser;
	}
}

// file_name should be path to file
QList<PublicationRecord> PublicationParser::parse(const QString &file_name) {
	CSVParser<27> &parser = *makePublicationParser(file_name);

	QList<PublicationRecord> records;
    int lineNum = 1;
	
	QString errorLog;
	QTextStream errorStream(&errorLog);
	
	int numErrors = 0;
	int numWarnings = 0;
	
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
			errorStream << "Error: Parser error: " << e.what() << " on line " << lineNum << "\n";
			numErrors++;
			continue;
		}
		
		if (!continueParsing) {
			break;
		}
		
        //validate memberName
        if (curr_record.memberName.isEmpty()) {
            errorStream << "Error: Missing member name on line " << lineNum << "\n";
			numErrors++;
            continue;
        }

        //validate primaryDomain
        if (curr_record.primaryDomain.isEmpty()) {
            errorStream << "Error: Missing primary domain on line " << lineNum << "\n";
			numErrors++;
            continue;
        }

        //validate publicationStatus
        if (curr_record.publicationStatus.isEmpty()) {
            errorStream << "Error: Missing publication status on line " << lineNum << "\n";
			numErrors++;
            continue;
        }
        //validate type
        if (curr_record.type.isEmpty()) {
            errorStream << "Error: Missing type on line " << lineNum << "\n";
			numErrors++;
            continue;
        }

        //validate date
		curr_record.date = parseDate(curr_date);
		if (!curr_record.date.isValid()) {
			errorStream << "Error: Invalid date '" << curr_date << "' on line " << lineNum << "\n";
			numErrors++;
			continue;
		}

        //validate role
        if (curr_record.role.isEmpty()) {
            errorStream << "Error: Missing role on line " << lineNum << "\n";
			numErrors++;
            continue;
        }

        //validate publishedIn
        if (curr_record.publishedIn.isEmpty()) {
            errorStream << "Error: Missing publication info on line " << lineNum << "\n";
			numErrors++;
            continue;
        }
		
        //validate authors
        if (curr_record.authors.isEmpty()) {
            errorStream << "Warning: Missing authors on line " << lineNum << "\n";
            numWarnings++;
        }

        //validate title
        if (curr_record.title.isEmpty()) {
            errorStream << "Error: Missing title on line " << lineNum << "\n";
			numErrors++;
            continue;
        }

        records.append(curr_record);
	}

	//show error dialog
	if (numErrors != 0 || numWarnings != 0) {
		ErrorListDialog errorDialog(errorLog, numErrors, numWarnings);
		errorDialog.exec();
	}
	
	return records;
}
