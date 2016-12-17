#ifndef DELETEPERSONHANDLER_H
#define DELETEPERSONHANDLER_H

#include <data/interface/datalyr_person.h>
#include <modelparser/interface/bytestreampersonparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class DeletePersonHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    DeletePersonHandler( Data::DataLyr_Person* dataLayer,
                         ModelParser::BytestreamPersonParser* parser,
                         QObject* parent=nullptr );
    virtual ~DeletePersonHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Person* m_dataLayer;
    ModelParser::BytestreamPersonParser* m_parser;
};

#endif // DELETEPERSONHANDLER_H
