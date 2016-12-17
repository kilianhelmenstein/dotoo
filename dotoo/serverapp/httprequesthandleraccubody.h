#ifndef HTTPREQUESETHANDLERACCUBODY_H
#define HTTPREQUESETHANDLERACCUBODY_H

#include "httprequesthandler.h"


class HttpRequesetHandlerAccuBody : public HttpRequestHandler
{
    Q_OBJECT
public:
    HttpRequesetHandlerAccuBody( HttpRequestHandler* handler,
                                 QObject* parent=nullptr );
    virtual ~HttpRequesetHandlerAccuBody();

public slots:
    /*!
     * \brief   Takes the http request and waits until the full body is received,
     *          then the request will be forwarded to m_handler.
     */
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    HttpRequestHandler* m_handler;      /*!< Request will be forwarded to this handler when body is recived fully. */

    QHttpRequest* m_request;            /*!< Store reference for later forwarding. */
    QHttpResponse* m_response;          /*!< Store reference for later forwarding. */
};

#endif // HTTPREQUESETHANDLERACCUBODY_H
