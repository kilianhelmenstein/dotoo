#include <QCoreApplication>

// Http Server classes:
#include <qhttpserver.h>
#include "httprequestrouter.h"
#include "httprequesthandleraccubody.h"

// REST API commands:
#include "rest/persons/getallpersonshandler.h"
#include "rest/persons/createpersonhandler.h"

// Data Layer classes:
#include "data/implementation/datalyr_personsql.h"
#include "data/implementation/datalyr_tasksql.h"

// Model parser:
#include "modelparser/person_json.h"
#include "modelparser/taskjson.h"



int main(int argc, char *argv[])
{
    using namespace Dotoo;

    QCoreApplication a(argc, argv);

    /* Parameters: */
    QString databaseName( "dotoo.db3" );
    QString tableNamePersons( "persons" );
    QString tableNameTasks( "tasks" );


    /* HttpServer layer: */
    QHttpServer server;
    HttpRequestRouter requestRouter( &server );
    QObject::connect( &server, SIGNAL(newRequest(QHttpRequest*,QHttpResponse*)),
                      &requestRouter, SLOT(handleRequest(QHttpRequest*,QHttpResponse*)) );

    /* Data Layer: */
    Data::DataLyr_Person* dataPersons = new Data::DataLyr_PersonSql( databaseName,
                                                                     tableNamePersons );
    Data::DataLyr_TaskSql* dataTasks = new Data::DataLyr_TaskSql( databaseName,
                                                                  tableNameTasks );

    /* Model parser: */
    ModelParser::BytestreamPersonParser* parserPerson = new ModelParser::JSONPersonParser;
    ModelParser::BytestreamTaskParser* parserTask = new ModelParser::JsonTaskParser;

    /* Application Layer: */
    /*********** NO IMPLEMENTATION YET ***********/
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_GET,
                                          "/persons$",
                                          new GetAllPersonsHandler( dataPersons, parserPerson, &server ));
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_POST,
                                          "/persons$",
                                          new HttpRequesetHandlerAccuBody(
                                            new CreatePersonHandler( dataPersons, parserPerson, &server )) );

    /* Adding all REST commands: */


    /* Start server: */
    if ( server.listen( 8080 ) )
    {
        return a.exec();
    } else
    {
        return 1;       // Break with error.
    }
}
