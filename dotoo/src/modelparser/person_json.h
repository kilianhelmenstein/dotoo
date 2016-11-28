#ifndef PERSON_JSON_H
#define PERSON_JSON_H

#include <QtGlobal>

#include "modelparser/interface/bytestreampersonparser.h"



namespace Dotoo {
namespace ModelParser {



class LIB_EXPORT JSONPersonParser : public BytestreamPersonParser
{
public:
    Person BytestreamIntoPerson( const QByteArray& bs ) const;
    QList<Person> BytestreamIntoPersonList( const QByteArray& bs ) const;

    QByteArray PersonIntoBytestream( const Person& person ) const;
    QByteArray PersonListIntoBytestream(const QList<Person>& personList ) const;
};


} // namespace ModelParser
} // namespace Dotoo

#endif // PERSON_JSON_H
