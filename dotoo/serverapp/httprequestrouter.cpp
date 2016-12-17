#include <QRegExp>

#include <qhttprequest.h>
#include <qhttpresponse.h>

#include "httprequestrouter.h"



HttpRequestRouter::HttpRequestRouter( QObject* parent )
    : HttpRequestHandler( parent )
{
}


bool HttpRequestRouter::registerRequestHandler( QHttpRequest::HttpMethod method,
                                                const QString& urlRegex,
                                                HttpRequestHandler* handler )
{
    // Check validity of pointer and whether urlRegex is already taken for
    // an other handler:
    if ( handler
         && !m_routerTable[method].contains( urlRegex ) )
    {
        m_routerTable[method][urlRegex] = handler;              // Add handler
        return true;
    }

    return false;   // Invalid input!
}


HttpRequestRouter::~HttpRequestRouter()
{}


void HttpRequestRouter::handleRequest( QHttpRequest* request,
                                       QHttpResponse* response )
{
    if ( m_routerTable.contains( request->method() ) )
    {
         for ( UrlRoutingMap::iterator handlerIt = m_routerTable[request->method()].begin()
               ; handlerIt != m_routerTable[request->method()].end()
               ; handlerIt++ )
         {
             QRegExp matchUrl( handlerIt.key() );

             if ( matchUrl.indexIn( request->url().toString() ) != -1 )
             {
                 // Current handler is the right one for this request!
                 handlerIt.value()->handleRequest( request,
                                                   response );
                 return;         // Nothing more to do.
             }
         }
    }


    // No handler is responsible for that request: Return 501 - Not implemented:
    response->writeHead( QHttpResponse::STATUS_NOT_IMPLEMENTED );
    response->end();
}
