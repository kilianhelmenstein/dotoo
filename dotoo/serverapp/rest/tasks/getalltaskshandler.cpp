#include "getalltaskshandler.h"


#include <qhttprequest.h>
#include <models/interface/task.h>

#include "utilz/tohttpcode.h"
#include "utilz/uriutilz.h"



using namespace Dotoo;



GetAllTasksHandler::GetAllTasksHandler( Data::DataLyr_Task* dataLayer,
                                        ModelParser::BytestreamTaskParser* parser,
                                        QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


GetAllTasksHandler::~GetAllTasksHandler()
{}


void GetAllTasksHandler::handleRequest( QHttpRequest* request,
                                        QHttpResponse* response )
{
    Q_UNUSED( request )
    QByteArray data;

    try
    {
        data = m_parser->TaskListIntoBytestream(
                    m_dataLayer->getAllTasks() );
        response->writeHead( QHttpResponse::STATUS_OK );
    } catch ( Data::Error_t e )
    {
        response->writeHead( HttpUtilz::DataErrorIntoHttpCode(e) );
    } catch (...)
    {
        response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
    }

    response->end( data );
}
