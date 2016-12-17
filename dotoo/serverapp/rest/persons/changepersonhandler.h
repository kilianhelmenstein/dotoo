#ifndef CHANGEPERSONHANDLER_H
#define CHANGEPERSONHANDLER_H

#include <data/interface/datalyr_person.h>
#include <modelparser/interface/bytestreampersonparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class ChangePersonHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    ChangePersonHandler( Data::DataLyr_Person* dataLayer,
                         ModelParser::BytestreamPersonParser* parser,
                         QObject* parent=nullptr );
    virtual ~ChangePersonHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Person* m_dataLayer;
    ModelParser::BytestreamPersonParser* m_parser;
};

#endif // CHANGEPERSONHANDLER_H
