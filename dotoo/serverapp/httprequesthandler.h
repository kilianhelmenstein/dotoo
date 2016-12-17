#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

#include <QObject>
#include <qhttpserverfwd.h>



class HttpRequestHandler : public QObject
{
    Q_OBJECT
public:
    HttpRequestHandler( QObject* parent=nullptr )
        : QObject( parent ) {}
    virtual ~HttpRequestHandler() {}

public slots:

    /*!
     * \brief           Handles a given http request and writes output into
     *                  response.
     *
     * \param[in]       QHttpRequest* request       Pointer to request object.
     *
     * \param[out]      QHttpResponse* response     Pointer to response object.
     */
    virtual void handleRequest( QHttpRequest* request,
                                QHttpResponse* response ) = 0;
};

#endif // HTTPREQUESTHANDLER_H
