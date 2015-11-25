#ifndef TEACHING_PARSER_H
#define TEACHING_PARSER_H

#include <QString>
#include <QList>

#include "../records/TeachingRecord.h"
#include "Parser.h"

class TeachingParser : public Parser {
 public:
    QList<TeachingRecord> parse(const QString &file_name);
};

#endif
