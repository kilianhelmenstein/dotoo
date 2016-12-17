#ifndef DELETETASKHANDLER_H
#define DELETETASKHANDLER_H

#include <data/interface/datalyr_task.h>
#include <modelparser/interface/bytestreamtaskparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class DeleteTaskHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    DeleteTaskHandler( Data::DataLyr_Task* dataLayer,
                       ModelParser::BytestreamTaskParser* parser,
                       QObject* parent=nullptr );
    virtual ~DeleteTaskHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Task* m_dataLayer;
    ModelParser::BytestreamTaskParser* m_parser;
};

#endif // DELETETASKHANDLER_H
