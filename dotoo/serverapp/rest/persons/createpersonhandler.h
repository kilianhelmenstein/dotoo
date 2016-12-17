#ifndef CREATEPERSONHANDLER_H
#define CREATEPERSONHANDLER_H

#include <data/interface/datalyr_person.h>
#include <modelparser/interface/bytestreampersonparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class CreatePersonHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    CreatePersonHandler( Data::DataLyr_Person* dataLayer,
                         ModelParser::BytestreamPersonParser* parser,
                         QObject* parent=nullptr );
    virtual ~CreatePersonHandler();


public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Person* m_dataLayer;
    ModelParser::BytestreamPersonParser* m_parser;
};

#endif // CREATEPERSONHANDLER_H
