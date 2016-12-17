#include "createtaskhandler.h"

#include <qhttprequest.h>
#include <models/interface/task.h>

#include "utilz/tohttpcode.h"



using namespace Dotoo;



CreateTaskHandler::CreateTaskHandler( Data::DataLyr_Task* dataLayer,
                                      ModelParser::BytestreamTaskParser* parser,
                                      QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


CreateTaskHandler::~CreateTaskHandler()
{}


void CreateTaskHandler::handleRequest( QHttpRequest* request,
                                       QHttpResponse* response )
{
    try
    {
        m_dataLayer->createTask( m_parser->BytestreamIntoTask( request->body() ) );
        response->writeHead( QHttpResponse::STATUS_OK );
    } catch ( Data::Error_t e )
    {
        response->writeHead( HttpUtilz::DataErrorIntoHttpCode(e) );
    } catch (...)
    {
        response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
    }

    response->end();
}
