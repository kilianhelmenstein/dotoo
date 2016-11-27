#ifndef PERSON_JSON_H
#define PERSON_JSON_H

#include <QtGlobal>

#include "libsymbolsexport.h"



class QByteArray;

namespace Dotoo {
class Person;
}


namespace ModelParser {

class LIB_EXPORT PersonJSON
{
public:
    static Dotoo::Person PersonFromJSON( const QByteArray& raw );
    static QByteArray JSONFromPerson( const Dotoo::Person& person );
};


} // namespace ModelParser

#endif // PERSON_JSON_H
