#ifndef PRESENTATION_RECORD_H
#define PRESENTATION_RECORD_H

#include <string>

struct PresentationRecord {
	std::string memberName;
	std::string primaryDomain;
	std::string date;
	std::string type;
	std::string role;
	std::string activityType;
	std::string geographicalScope;
	std::string host;
	std::string country;
	std::string province;
	std::string city;
	std::string numberOfAttendees;
	std::string hours;
	std::string teachingScore;
	std::string educationPresentation;
	std::string remarks;
	std::string authorship;
	std::string title;
	std::string restOfCitation;
	std::string personalRemuneration;
};

#endif
