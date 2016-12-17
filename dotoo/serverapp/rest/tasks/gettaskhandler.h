#ifndef GETTASKHANDLER_H
#define GETTASKHANDLER_H


#include <data/interface/datalyr_task.h>
#include <modelparser/interface/bytestreamtaskparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class GetTaskHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    GetTaskHandler( Data::DataLyr_Task* dataLayer,
                       ModelParser::BytestreamTaskParser* parser,
                       QObject* parent=nullptr );
    virtual ~GetTaskHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Task* m_dataLayer;
    ModelParser::BytestreamTaskParser* m_parser;
};

#endif // GETTASKHANDLER_H
