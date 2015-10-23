#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "../../external/csv.h"

class Parser {
	template <unsigned column_count>
	using CSVParser = io::CSVReader<column_count, 
									trim_chars<' '>, 
									double_quote_escape<',', '"'>, 
									throw_on_overflow,
									empty_line_comment>;
	
	static const io::ignore_column column_policy = io::ignore_no_column;
};

#endif
