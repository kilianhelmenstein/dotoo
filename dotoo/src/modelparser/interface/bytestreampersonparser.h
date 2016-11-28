#ifndef BYTESTREAMPERSONPARSER_H
#define BYTESTREAMPERSONPARSER_H

#include <QList>

#include "project/libsymbolsexport.h"
#include "models/interface/decl/persondecl.h"



class QByteArray;


namespace Dotoo {
namespace ModelParser {


class LIB_EXPORT BytestreamPersonParser
{
public:
    virtual ~BytestreamPersonParser() {}

    virtual Person BytestreamIntoPerson( const QByteArray& bs ) const = 0;
    virtual QList<Person> BytestreamIntoPersonList( const QByteArray& bs ) const = 0;

    virtual QByteArray PersonIntoBytestream( const Person& p ) const = 0;
    virtual QByteArray PersonListIntoBytestream( const QList<Person>& p ) const = 0;
};


} // namespace ModelParser
} // namespace Dotoo

#endif // BYTESTREAMPERSONPARSER_H
