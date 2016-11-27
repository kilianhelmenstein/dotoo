#include <QByteArray>
#include "parsing/json.h"

#include "person_json.h"
#include "person.h"
#include "types/persontypes.h"


using namespace ModelParser;

using json = nlohmann::json;    /* For convinience. */



Dotoo::Person PersonJSON::PersonFromJSON( const QByteArray& raw )
{
    json jsonData = json::parse( raw.data() );

    return Dotoo::Person( jsonData["id"],
                          Dotoo::PersonName_t(
                            QString::fromStdString(jsonData["name"]),
                            QString::fromStdString(jsonData["forename"])
                          ),
                          QString::fromStdString(jsonData["comment"]) );
}



QByteArray PersonJSON::JSONFromPerson( const Dotoo::Person& person )
{
    json jsonData = {
        { "id", person.getId() },
        { "name", person.getName().name.toStdString() },
        { "forename", person.getName().forename.toStdString() },
        { "comment", person.getComment().toStdString() }
    };

    return QByteArray( jsonData.dump().data(), jsonData.size() );
}
