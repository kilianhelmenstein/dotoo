#ifndef HTTPREQUESTROUTER_H
#define HTTPREQUESTROUTER_H

#include <QMap>

#include <qhttprequest.h>

#include "httprequesthandler.h"



class HttpRequestRouter : public HttpRequestHandler
{
    Q_OBJECT
public:
    HttpRequestRouter( QObject* parent=nullptr );
    virtual ~HttpRequestRouter();

    /*!
     * \brief   Registers a new HttpRequestHandler to the request router.
     *          The request will be forwarded to the handler if regular expression
     *          urlRegex finds matches within url.
     *
     * \param   QHttpRequest::HttpMethod method     The http method for the handler.
     *
     * \param   const QString& urlRegex             The regular expression that has to match on the request url.
     *
     * \param   HttpRequestHandler* handler         If method and url matches, request will be forwarded to this object.
     *
     * \return  bool        true  - Handler was registered successfully.
     *                      false - Handler could not be registered. May be urlRegex is already taken
     *                              for an other handler.
     */
    bool registerRequestHandler( QHttpRequest::HttpMethod method,
                                 const QString& urlRegex,
                                 HttpRequestHandler* handler );


public slots:
    /*!
     * \brief   See documentation in "httprequesthandler.h"
     *
     * \note    Very simple and inefficient implementation yet!
     *          TODO: Route urls by using a binary search tree.
     */
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );


private:
    typedef QMap<QString, HttpRequestHandler*> UrlRoutingMap;
    typedef QMap<QHttpRequest::HttpMethod, UrlRoutingMap> HttpMethodToRouterMap;

    HttpMethodToRouterMap m_routerTable;    /*!< Maps url condition to request handler object. */
};

#endif // HTTPREQUESTROUTER_H
