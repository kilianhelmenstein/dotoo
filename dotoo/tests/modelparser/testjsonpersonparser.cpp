#include "testjsonpersonparser.h"

#include "modelparser/person_json.h"
#include "models/interface/person.h"
#include "models/interface/types/persontypes.h"



using namespace Dotoo;
using namespace ModelParser;



void TestkJsonPersonParser::PersonToJsonToPerson()
{
    Person testPerson( 10,
                       PersonName_t( "test_forename", "test_name" ),
                       "only a test" );

    JSONPersonParser parser;
    QByteArray bs = parser.PersonIntoBytestream( testPerson );
    qDebug() << QString( bs );
    Person testPerson2( parser.BytestreamIntoPerson( bs ) );

    QVERIFY( testPerson == testPerson2 );
}
