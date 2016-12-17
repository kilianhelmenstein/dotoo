#include <qhttpresponse.h>

#include <models/interface/person.h>

#include "getallpersonshandler.h"
#include "utilz/tohttpcode.h"



using namespace Dotoo;



GetAllPersonsHandler::GetAllPersonsHandler( Data::DataLyr_Person* dataLayer,
                                            ModelParser::BytestreamPersonParser* parser,
                                            QObject* parent )
    : HttpRequestHandler( parent ),
      m_dataLayer( dataLayer ),
      m_parser( parser )
{}


GetAllPersonsHandler::~GetAllPersonsHandler()
{}


void GetAllPersonsHandler::handleRequest( QHttpRequest* request,
                                          QHttpResponse* response )
{
    Q_UNUSED( request )
    QByteArray data;

    try
    {
        data = m_parser->PersonListIntoBytestream(
                    m_dataLayer->getAllPersons() );
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
