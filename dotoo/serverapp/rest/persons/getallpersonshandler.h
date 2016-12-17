#ifndef GETALLPERSONSHANDLER_H
#define GETALLPERSONSHANDLER_H

#include <data/interface/datalyr_person.h>
#include <modelparser/interface/bytestreampersonparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class GetAllPersonsHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    GetAllPersonsHandler( Data::DataLyr_Person* dataLayer,
                          ModelParser::BytestreamPersonParser* parser,
                          QObject* parent=nullptr );
    virtual ~GetAllPersonsHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Person* m_dataLayer;
    ModelParser::BytestreamPersonParser* m_parser;
};

#endif // GETALLPERSONSHANDLER_H
