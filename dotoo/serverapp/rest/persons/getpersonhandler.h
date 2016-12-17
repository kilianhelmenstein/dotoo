#ifndef GETPERSONHANDLER_H
#define GETPERSONHANDLER_H


#include <data/interface/datalyr_person.h>
#include <modelparser/interface/bytestreampersonparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class GetPersonHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    GetPersonHandler( Data::DataLyr_Person* dataLayer,
                      ModelParser::BytestreamPersonParser* parser,
                      QObject* parent=nullptr );
    virtual ~GetPersonHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Person* m_dataLayer;
    ModelParser::BytestreamPersonParser* m_parser;
};

#endif // GETPERSONHANDLER_H
