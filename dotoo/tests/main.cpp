#include <QCoreApplication>
#include <QDebug>

#include "testdatalyr_personsql.h"



int main(int argc, char *argv[])
{
    int status = 0;     /* Common state for all unit tests. */

    /* Define function that executes a test: */
    auto ProcessTest = [&status, argc, argv](QObject* obj) {
        status |= QTest::qExec(obj, argc, argv);
        delete obj;
    };

    /* Process all tests: */
    ProcessTest( new TestDataLyr_PersonSql() );

    /* Return common state. */
    return status;
}
