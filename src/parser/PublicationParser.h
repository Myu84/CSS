#ifndef PUBLICATION_PARSER_H
#define PUBLICATION_PARSER_H

#include <QString>
#include <QList>

#include "../records/PublicationRecord.h"
#include "Parser.h"

class PublicationParser : public Parser {
 public:
    QList<PublicationRecord> parse(const QString &file_name);
};

#endif
