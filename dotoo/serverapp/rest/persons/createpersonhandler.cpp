#include "createpersonhandler.h"

#include <qhttprequest.h>
#include <models/interface/person.h>
#include "utilz/tohttpcode.h"



using namespace Dotoo;



CreatePersonHandler::CreatePersonHandler( Data::DataLyr_Person* dataLayer,
                                          ModelParser::BytestreamPersonParser* parser,
                                          QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


CreatePersonHandler::~CreatePersonHandler()
{
}


void CreatePersonHandler::handleRequest( QHttpRequest* request,
                                         QHttpResponse* response )
{
    try
    {
        m_dataLayer->createPerson( m_parser->BytestreamIntoPerson( request->body() ) );
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

