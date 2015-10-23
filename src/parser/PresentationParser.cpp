#include <string>
#include <vector>

#include "../records/PresentationRecord.h"
#include "PresentationParser.h"

using namespace std;

// file_name should be path to file
vector<PresentationRecord> PresentationParser::parse(string file_name) {
	CSVParser parser(file_name);

	parser.read_header(column_policy,
		"Member Name",
		"Primary Domain",
		"Date",
		"Type",
		"Role",
		"Activity Type",
		"Geographical Scope",
		"Host",
		"Country",
		"Province",
		"City",
		"Number of Attendees",
		"Hours",
		"Teaching Effectiveness Score",
		"Education Presentation",
		"Remarks",
		"Authorship",
		"Title",
		"Rest of Citation",
		"Personal Remuneration");
	
	// error checking + column ignoring should be done in the while loop
	while (in.read_row(memberName, primaryDomain,
		date, type, role, activityType, 
		geographicalScope, host, country, 
		province, city, numberOfAttendees, 
		hours, teachingScore, 
		educationPresentation, remarks, authorship, title, restOfCitation, personalRemuneration)) {

		cout << "Member Name: " << memberName << " Primary Domain: " << primaryDomain << " Type: " << type << " Authorship: " << authorship;

		cin.ignore();
		
		break;
	}
}
