#include <qhttprequest.h>
#include <qhttpresponse.h>

#include "deletepersonhandler.h"
#include "utilz/tohttpcode.h"
#include "utilz/uriutilz.h"



DeletePersonHandler::DeletePersonHandler( Data::DataLyr_Person* dataLayer,
                                          ModelParser::BytestreamPersonParser* parser,
                                          QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


DeletePersonHandler::~DeletePersonHandler()
{}


void DeletePersonHandler::handleRequest( QHttpRequest* request,
                                         QHttpResponse* response )
{
    QString selectedPerson( UriUtilz::FindResourceId( request->url().toString(),
                                                      "persons" ) );

    if ( selectedPerson.isEmpty() ) // Check given id
    {   // Invalid uri format: missing resource id
        response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
    } else
    {   // Resource id could be parsed. Try getting person data:
        try
        {
            m_dataLayer->deletePerson( selectedPerson.toInt() );
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
