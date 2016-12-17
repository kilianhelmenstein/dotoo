#include <qhttprequest.h>

#include "httprequesthandleraccubody.h"

HttpRequesetHandlerAccuBody::HttpRequesetHandlerAccuBody( HttpRequestHandler* handler,
                                                          QObject* parent )
    : HttpRequestHandler( parent ),
      m_handler( handler )
{

}


HttpRequesetHandlerAccuBody::~HttpRequesetHandlerAccuBody()
{}


void HttpRequesetHandlerAccuBody::handleRequest( QHttpRequest* request,
                                                 QHttpResponse* response )
{
    m_request = request;
    m_response = response;



    /* Forward respone when body is received fully: */
    m_request->storeBody();
    connect( m_request, &QHttpRequest::end,
             [&](){ m_handler->handleRequest(m_request, m_response); } );
}
