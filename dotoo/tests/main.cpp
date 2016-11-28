#include <QCoreApplication>
#include <QDebug>

// Data layer:
#include "testdatalyr_personsql.h"

// Model parser:
#include "modelparser/testjsontaskparser.h"
#include "modelparser/testjsonpersonparser.h"



int main(int argc, char *argv[])
{
    int status = 0;     /* Common state for all unit tests. */

    /* Define function that executes a test: */
    auto ProcessTest = [&status, argc, argv](QObject* obj) {
        status |= QTest::qExec(obj, argc, argv);
        delete obj;
    };


    /* Process all tests: */
    /* ================== */

    // Data layer:
    ProcessTest( new TestDataLyr_PersonSql() );

    // Model parser:
    ProcessTest( new TestJsonTaskParser() );
    ProcessTest( new TestkJsonPersonParser() );

    /* Return common state. */
    return status;
}
