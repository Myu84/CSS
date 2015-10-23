#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "../../external/csv.h"

class Parser {
 protected:
	template <unsigned column_count>
	using CSVParser = io::CSVReader<column_count, 
									io::trim_chars<' '>, 
									io::double_quote_escape<',', '"'>, 
									io::throw_on_overflow,
									io::empty_line_comment>;
	
	static const io::ignore_column column_policy = io::ignore_no_column;
};

#endif
