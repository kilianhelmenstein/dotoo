#include <qhttprequest.h>
#include <qhttpresponse.h>

#include <models/interface/person.h>

#include "getpersonhandler.h"
#include "utilz/tohttpcode.h"
#include "utilz/uriutilz.h"



using namespace Dotoo;



GetPersonHandler::GetPersonHandler( Data::DataLyr_Person* dataLayer,
                                    ModelParser::BytestreamPersonParser* parser,
                                    QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


GetPersonHandler::~GetPersonHandler()
{}


void GetPersonHandler::handleRequest( QHttpRequest* request,
                                      QHttpResponse* response )
{
    QByteArray personData;      // Data output
    QString selectedPerson( UriUtilz::FindResourceId( request->url().toString(),
                                                      "persons" ) );

    if ( selectedPerson.isEmpty() ) // Check given id
    {   // Invalid uri format: missing resource id
        response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
    } else
    {   // Resource id could be parsed. Try getting person data:
        try
        {
            personData = m_parser->PersonIntoBytestream(
                            m_dataLayer->getPerson( selectedPerson.toInt() ) );
            response->writeHead( QHttpResponse::STATUS_OK );
        } catch ( Data::Error_t e )
        {
            response->writeHead( HttpUtilz::DataErrorIntoHttpCode(e) );
        } catch (...)
        {
            response->writeHead( QHttpResponse::STATUS_BAD_REQUEST );
        }
    }

    response->end( personData );
}
