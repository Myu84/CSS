#ifndef PRESENTATION_PARSER_H
#define PRESENTATION_PARSER_H

#include <string>
#include <vector>

#include "../records/PresentationRecord.h"
#include "Parser.h"

class PresentationParser : Parser {
 public:
	std::vector<PresentationRecord> parse(std::string file_name);
};

#endif
