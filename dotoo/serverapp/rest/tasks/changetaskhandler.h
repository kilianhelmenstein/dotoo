#ifndef CHANGETASKHANDLER_H
#define CHANGETASKHANDLER_H


#include <data/interface/datalyr_task.h>
#include <modelparser/interface/bytestreamtaskparser.h>

#include "httprequesthandler.h"


using namespace Dotoo;



class ChangeTaskHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    ChangeTaskHandler( Data::DataLyr_Task* dataLayer,
                       ModelParser::BytestreamTaskParser* parser,
                       QObject* parent=nullptr );
    virtual ~ChangeTaskHandler();

public slots:
    void handleRequest( QHttpRequest* request,
                        QHttpResponse* response );

private:
    Data::DataLyr_Task* m_dataLayer;
    ModelParser::BytestreamTaskParser* m_parser;
};

#endif // CHANGETASKHANDLER_H
