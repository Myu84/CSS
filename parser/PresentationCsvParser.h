#pragma once
#include <string>

using namespace std;

class PresentationCsvParser {
public:
	// actually, instead of returning void it should return something useful like map or list
	void parse(string file_name);
};

// defined data class to hold Presentation info
class PresentationBean {
private:
	string m_memberName,
		m_primaryDomain,
		m_date,
		m_type,
		m_role,
		m_activityType,
		m_geographicalScope,
		m_host,
		m_country,
		m_province,
		m_city,
		m_numberOfAttendees,
		m_hours,
		m_teachingScore,
		m_educationPresentation,
		m_remarks,
		m_authorship,
		m_title,
		m_restOfCitation,
		m_personalRemuneration;

};
