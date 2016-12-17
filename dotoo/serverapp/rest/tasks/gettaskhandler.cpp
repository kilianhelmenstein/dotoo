#include "gettaskhandler.h"

#include <qhttprequest.h>
#include <models/interface/task.h>

#include "utilz/tohttpcode.h"
#include "utilz/uriutilz.h"



using namespace Dotoo;



GetTaskHandler::GetTaskHandler( Data::DataLyr_Task* dataLayer,
                                ModelParser::BytestreamTaskParser* parser,
                                QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


GetTaskHandler::~GetTaskHandler()
{}


void GetTaskHandler::handleRequest( QHttpRequest* request,
                                    QHttpResponse* response )
{
    QByteArray TaskData;      // Data output
    QString selectedTask( UriUtilz::FindResourceId( request->url().toString(),
                                                    "tasks" ) );

    if ( selectedTask.isEmpty() ) // Check given id
    {   // Invalid uri format: missing resource id
        response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
    } else
    {   // Resource id could be parsed. Try getting Task data:
        try
        {
            TaskData = m_parser->TaskIntoBytestream(
                        m_dataLayer->getTask( selectedTask.toInt() ) );
            response->writeHead( QHttpResponse::STATUS_OK );
        } catch ( Data::Error_t e )
        {
            response->writeHead( HttpUtilz::DataErrorIntoHttpCode(e) );
        } catch (...)
        {
            response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
        }
    }

    response->end( TaskData );
}
