#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <QString>
#include <QDate>
#include "../../external/csv.h"

class Parser {
 public:
	template <unsigned column_count>
	using CSVParser = io::CSVReader<column_count, 
									io::trim_chars<' '>, 
									io::double_quote_escape<',', '"'>, 
									io::throw_on_overflow,
									io::empty_line_comment>;

	static const io::ignore_column column_policy = io::ignore_extra_column;

 protected:
	inline QDate parseDate(const QString &date_str) {
		QDate output = QDate::fromString(date_str, "yyyy/M/d");
		if (!output.isValid()) {
			output = QDate::fromString(date_str, "yyyy/M");
			if (!output.isValid()) {
				output = QDate::fromString(date_str, "yyyy");
			}
		}
		
		return output;
	}
	
	inline bool parseBool(const QString &bool_str, bool *ok = nullptr) {
		if (bool_str.toLower() == "true" || bool_str == "1") {
			if (ok)
				*ok = true;
			return true;
		} else if (bool_str.toLower() == "false" || bool_str == "0") {
			if (ok)
				*ok = true;
			return false;
		} else {
			if (ok)
				*ok = false;
			return false;
		}
	}
	
	inline double parseMoney(QString money_str, bool *ok = nullptr) {
		money_str.remove('$').remove(',');
		double val = money_str.toDouble(ok);
		
		if (ok && *ok && val < 0)
			*ok = false;
		return val;
	}
};

#endif
