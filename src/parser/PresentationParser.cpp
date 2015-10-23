#include <string>
#include <vector>

#include "../records/PresentationRecord.h"
#include "PresentationParser.h"

using namespace std;

// file_name should be path to file
vector<PresentationRecord> PresentationParser::parse(string file_name) {
	CSVParser<20> parser(file_name);

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
	
	vector<PresentationRecord> records;
	bool done = false;
	
	while (!done) {
		PresentationRecord curr_record;
		
		done = parser.read_row(curr_record.memberName, 
			curr_record.primaryDomain,
			curr_record.date, 
			curr_record.type, 
			curr_record.role, 
			curr_record.activityType, 
			curr_record.geographicalScope, 
			curr_record.host, 
			curr_record.country, 
			curr_record.province, 
			curr_record.city, 
			curr_record.numberOfAttendees, 
			curr_record.hours, 
			curr_record.teachingScore, 
			curr_record.educationPresentation, 
			curr_record.remarks, 
			curr_record.authorship, 
			curr_record.title, 
			curr_record.restOfCitation, 
			curr_record.personalRemuneration);
		
		/*
			Error checking goes here.
		*/
		
		records.push_back(curr_record);
	}
	
	return records;
}
