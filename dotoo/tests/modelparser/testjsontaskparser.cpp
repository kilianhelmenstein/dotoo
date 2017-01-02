#include <QDate>

#include "testjsontaskparser.h"

#include "models/interface/task.h"
#include "modelparser/taskjson.h"



using namespace Dotoo;
using namespace ModelParser;



void TestJsonTaskParser::TaskToJsonToTask()
{
    Task testTask( 10,
                   "test",
                   false,
                   1,
                   1,
                   QDate::fromString("2016-11-11"),
                   QDate::fromString("2016-11-22"),
                   Dotoo::VeryImportant,
                   1,
                   "only a test" );

    JsonTaskParser parser;
    QByteArray bs = parser.TaskIntoBytestream( testTask );

    Task testTask2( parser.BytestreamIntoTask( bs ) );

    QVERIFY( testTask == testTask2 );
}
