#ifndef GRANT_PARSER_H
#define GRANT_PARSER_H

#include <QString>
#include <QList>

#include "../records/GrantRecord.h"
#include "Parser.h"

class GrantParser : public Parser {
 public:
    QList<GrantRecord> parse(const QString &file_name);
};

#endif
