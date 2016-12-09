#include <QCoreApplication>

// Http Server classes:
#include <qhttpserver.h>
#include "httprequestrouter.h"
#include "httprequesthandleraccubody.h"

// REST API commands:
#include "rest/persons/createpersonhandler.h"
#include "rest/persons/getallpersonshandler.h"
#include "rest/persons/getpersonhandler.h"
#include "rest/persons/changepersonhandler.h"
#include "rest/persons/deletepersonhandler.h"

#include "rest/tasks/createtaskhandler.h"
#include "rest/tasks/getalltaskshandler.h"
#include "rest/tasks/gettaskhandler.h"
#include "rest/tasks/changetaskhandler.h"
#include "rest/tasks/deletetaskhandler.h"

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
    QString databaseConnectionPersons( "persons_con" );
    QString databaseConnectionTasks( "tasks_con" );
    QString tableNamePersons( "persons" );
    QString tableNameTasks( "tasks" );


    /* HttpServer layer: */
    QHttpServer server;
    HttpRequestRouter requestRouter( &server );
    QObject::connect( &server, SIGNAL(newRequest(QHttpRequest*,QHttpResponse*)),
                      &requestRouter, SLOT(handleRequest(QHttpRequest*,QHttpResponse*)) );

    /* Data Layer: */
    Data::DataLyr_Person* dataPersons = new Data::DataLyr_PersonSql( databaseConnectionPersons,
                                                                     databaseName,
                                                                     tableNamePersons );
    Data::DataLyr_TaskSql* dataTasks = new Data::DataLyr_TaskSql( databaseConnectionTasks,
                                                                  databaseName,
                                                                  tableNameTasks );

    /* Model parser: */
    ModelParser::BytestreamPersonParser* parserPerson = new ModelParser::JSONPersonParser;
    ModelParser::BytestreamTaskParser* parserTask = new ModelParser::JsonTaskParser;

    /* Application Layer: */
    /*********** NO IMPLEMENTATION YET ***********/

    /* Adding all REST commands: */
    // Person resources:
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_POST,
                                          "/persons$",
                                          new HttpRequesetHandlerAccuBody(
                                              new CreatePersonHandler( dataPersons, parserPerson, &server ), &server ) );
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_GET,
                                          "/persons$",
                                          new GetAllPersonsHandler( dataPersons, parserPerson, &server ));
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_GET,
                                          "/persons/[0-9]{1,4}$",
                                          new GetPersonHandler( dataPersons, parserPerson, &server ));
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_PUT,
                                          "/persons/[0-9]{1,4}$",
                                          new HttpRequesetHandlerAccuBody(
                                              new ChangePersonHandler( dataPersons, parserPerson, &server ), &server ) );
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_DELETE,
                                          "/persons/[0-9]{1,4}$",
                                          new DeletePersonHandler( dataPersons, parserPerson, &server ));

    // Task resources:
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_POST,
                                          "/tasks$",
                                          new HttpRequesetHandlerAccuBody(
                                              new CreateTaskHandler( dataTasks, parserTask, &server ), &server ) );
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_GET,
                                          "/tasks$",
                                          new GetAllTasksHandler( dataTasks, parserTask, &server ));
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_GET,
                                          "/tasks/[0-9]{1,4}$",
                                          new GetTaskHandler( dataTasks, parserTask, &server ));
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_PUT,
                                          "/tasks/[0-9]{1,4}$",
                                          new HttpRequesetHandlerAccuBody(
                                              new ChangeTaskHandler( dataTasks, parserTask, &server ), &server ) );
    requestRouter.registerRequestHandler( QHttpRequest::HTTP_DELETE,
                                          "/tasks/[0-9]{1,4}$",
                                          new DeleteTaskHandler( dataTasks, parserTask, &server ));

    /* Start server: */
    if ( server.listen( 8080 ) )
    {
        return a.exec();
    } else
    {
        return 1;       // Break with error.
    }
}
