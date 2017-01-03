#ifndef PERSONTYPES_H
#define PERSONTYPES_H


/********************* Includes *********************/

#include <QString>



/******************** Namespaces ********************/

namespace Dotoo {

typedef struct _PersonName
{
public:
    QString forename;
    QString name;

public:
    _PersonName( const QString& argForename, const QString& argName )
        : forename( argForename ),
          name( argName )
    {}

    bool operator ==( const _PersonName& other )
    {
        return (forename == other.forename && name == other.name);
    }
    bool operator !=( const _PersonName& other ) { return !(*this == other); }

    QString fullName( bool forenameLeading=true) const
    {
        if ( forenameLeading )
        {
            return forename + " " + name;
        } else
        {
            return name + " " + forename;
        }
    }

} PersonName_t;



/********************* Typedefs *********************/




} // namespace Dotoo
#endif // PERSONTYPES_H
