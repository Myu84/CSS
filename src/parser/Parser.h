#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "../../external/csv.h"

class Parser {
	using CSVParser = io::CSVReader<20, trim_chars<' '>, double_quote_escape<',', '\"'>>;
	
	static const io::ignore_column column_policy = io::ignore_extra_column;
};

#endif
