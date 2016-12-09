#include <QByteArray>
#include <QList>

#include "parsing/json.h"

#include "person_json.h"
#include "types/persontypes.h"
#include "person.h"



using namespace Dotoo;
using namespace ModelParser;

using json = nlohmann::json;    /* For convinience. */



Person JsonToPerson( const json& jsonData )
{
    return Dotoo::Person( jsonData.count("id") ? static_cast<UniqueId>(jsonData["id"]) : 0,
                          Dotoo::PersonName_t(
                            QString::fromStdString(jsonData["forename"]),
                            QString::fromStdString(jsonData["name"])
                          ),
                          QString::fromStdString(jsonData["comment"]) );
}


json PersonToJson( const Person& person )
{
    json jsonData = {
        { "id", person.getId() },
        { "name", person.getName().name.toStdString() },
        { "forename", person.getName().forename.toStdString() },
        { "comment", person.getComment().toStdString() }
    };

    return jsonData;
}



Person JSONPersonParser::BytestreamIntoPerson( const QByteArray& bs ) const
{
    json jsonData = json::parse( bs.data() );
    return JsonToPerson( jsonData );
}


QList<Person> JSONPersonParser::BytestreamIntoPersonList( const QByteArray& bs ) const
{
    QList<Person> personList;
    json jsonDataAll = json::parse( bs.data() );

    /* Step through json array and create all persons: */
    for ( std::size_t i = 0 ; i < jsonDataAll.size() ; i++ )
    {
        json jsonData = jsonDataAll.at(i);
        personList.append( JsonToPerson(jsonData) );
    }

    return personList;
}


QByteArray JSONPersonParser::PersonIntoBytestream( const Person& person ) const
{
    json jsonData = PersonToJson( person );
    return QByteArray( jsonData.dump().data() );
}


QByteArray JSONPersonParser::PersonListIntoBytestream( const QList<Person>& personList ) const
{
    json jsonDataAll;

    for ( QList<Person>::const_iterator itPerson = personList.begin()
          ; itPerson != personList.end()
          ; itPerson++ )
    {
        jsonDataAll.push_back( PersonToJson(*itPerson) );
    }

    return QByteArray( jsonDataAll.dump().data() );
}
