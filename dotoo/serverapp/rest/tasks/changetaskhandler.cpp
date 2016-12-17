#include "changetaskhandler.h"

#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <models/interface/task.h>

#include "utilz/tohttpcode.h"
#include "utilz/uriutilz.h"



using namespace Dotoo;



ChangeTaskHandler::ChangeTaskHandler( Data::DataLyr_Task* dataLayer,
                                      ModelParser::BytestreamTaskParser* parser,
                                      QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


ChangeTaskHandler::~ChangeTaskHandler()
{}


void ChangeTaskHandler::handleRequest( QHttpRequest* request,
                                       QHttpResponse* response )
{
    QString selectedTask( UriUtilz::FindResourceId( request->url().toString(),
                                                    "tasks" ) );

    if ( selectedTask.isEmpty() ) // Check given id
    {   // Invalid uri format: missing resource id
        response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
    } else
    {   // Resource id could be parsed. Try getting person data:
        try
        {
            // Create person with changed data and set right id:
            Task changedTask = m_parser->BytestreamIntoTask( request->body() );
            changedTask.setId( selectedTask.toInt() );

            // Try to change person:
            m_dataLayer->changeTask( changedTask );
            response->writeHead( QHttpResponse::STATUS_OK );
        } catch ( Data::Error_t e )
        {
            response->writeHead( HttpUtilz::DataErrorIntoHttpCode(e) );
        } catch (...)
        {
            response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
        }
    }

    response->end();
}

