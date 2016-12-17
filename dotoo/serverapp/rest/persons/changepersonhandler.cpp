#include "changepersonhandler.h"

#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <models/interface/person.h>

#include "utilz/tohttpcode.h"
#include "utilz/uriutilz.h"



ChangePersonHandler::ChangePersonHandler( Data::DataLyr_Person* dataLayer,
                                          ModelParser::BytestreamPersonParser* parser,
                                          QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


ChangePersonHandler::~ChangePersonHandler()
{}


void ChangePersonHandler::handleRequest( QHttpRequest* request,
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
            // Create person with changed data and set right id:
            Person changedPerson = m_parser->BytestreamIntoPerson( request->body() );
            changedPerson.setId( selectedPerson.toInt() );

            // Try to change person:
            m_dataLayer->changePerson( changedPerson );
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
