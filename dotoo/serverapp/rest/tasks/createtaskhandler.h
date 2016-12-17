#ifndef CREATETASKHANDLER_H
#define CREATETASKHANDLER_H


#include <data/interface/datalyr_task.h>
#include <modelparser/interface/bytestreamtaskparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class CreateTaskHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    CreateTaskHandler( Data::DataLyr_Task* dataLayer,
                       ModelParser::BytestreamTaskParser* parser,
                       QObject* parent=nullptr );
    virtual ~CreateTaskHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Task* m_dataLayer;
    ModelParser::BytestreamTaskParser* m_parser;
};

#endif // CREATETASKHANDLER_H
