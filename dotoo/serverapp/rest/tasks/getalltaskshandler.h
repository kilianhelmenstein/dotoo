#ifndef GETALLTASKSHANDLER_H
#define GETALLTASKSHANDLER_H

#include <data/interface/datalyr_task.h>
#include <modelparser/interface/bytestreamtaskparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class GetAllTasksHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    GetAllTasksHandler( Data::DataLyr_Task* dataLayer,
                       ModelParser::BytestreamTaskParser* parser,
                       QObject* parent=nullptr );
    virtual ~GetAllTasksHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Task* m_dataLayer;
    ModelParser::BytestreamTaskParser* m_parser;
};

#endif // GETALLTASKSHANDLER_H
