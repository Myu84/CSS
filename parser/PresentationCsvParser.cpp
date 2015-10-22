#include "stdafx.h"
#include "PresentationCsvParser.h"
#include <iostream>
#include <fstream>
#include "csv.h"

// file_name should be path to file
void PresentationCsvParser::parse(string file_name)
{
	string memberName,
		primaryDomain,
		date,
		type,
		role,
		activityType,
		geographicalScope,
		host,
		country,
		province,
		city,
		numberOfAttendees,
		hours,
		teachingScore,
		educationPresentation,
		remarks,
		authorship,
		title,
		restOfCitation,
		personalRemuneration;

	io::CSVReader<20, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in(file_name);

	in.read_header(io::ignore_extra_column,
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
