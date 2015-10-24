#ifndef PRESENTATION_PARSER_H
#define PRESENTATION_PARSER_H

#include <QString>
#include <QList>

#include "../records/PresentationRecord.h"
#include "Parser.h"

class PresentationParser : public Parser {
 public:
	QList<PresentationRecord> parse(QString file_name);
};

#endif
