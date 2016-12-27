#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "asyncdatalyr_taskhttp.h"
#include "data/utils/http.h"
#include "models/interface/task.h"
#include "modelparser/interface/bytestreamtaskparser.h"


using namespace Dotoo;
using namespace Dotoo::Data;
using namespace Dotoo::ModelParser;



AsyncDataLyr_TaskHttp::AsyncDataLyr_TaskHttp( const QString& url,
                                              const QString& resourceCollection,
                                              BytestreamTaskParser* parser)
    : m_url( url ),
      m_resourceCollection( resourceCollection ),
      m_parser( parser ),
      m_networkAccess( nullptr )
{
    m_networkAccess = new QNetworkAccessManager( this );
    m_networkAccess->connectToHost( url );
    connect( m_networkAccess, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(onNetworkReply(QNetworkReply*)) );
}



AsyncDataLyr_TaskHttp::~AsyncDataLyr_TaskHttp()
{}


AsyncDataLyr_TaskResponse* AsyncDataLyr_TaskHttp::getAllTasks()
{
    AsyncDataLyr_TaskResponse* retVal = new AsyncDataLyr_TaskResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2").arg( m_url, m_resourceCollection ) );
    QNetworkReply* reply = m_networkAccess->get( request );

    auto handleResponse = [this, retVal, reply]()
    {
        QList<Task>* allTasks = nullptr;

        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        Error_t errorCode = HttpUtilz::DataErrorIntoHttpCode( statusCode );
        if ( errorCode == Data::None )
        {
            try {
                allTasks = new QList<Task>( m_parser->BytestreamIntoTaskList( reply->readAll() ) );
            } catch (...) {
                errorCode = Data::InvalidFormat;
            }
        }

        emit retVal-> responseGetAllTasks( allTasks, errorCode );
    };

    connect( reply, &QNetworkReply::readyRead, handleResponse );
    return retVal;
}


AsyncDataLyr_TaskResponse* AsyncDataLyr_TaskHttp::getTask( const UniqueId taskId )
{
    AsyncDataLyr_TaskResponse* retVal = new AsyncDataLyr_TaskResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( taskId ) ) );

    QNetworkReply* reply = m_networkAccess->get( request );

    auto handleResponse = [this, retVal, reply]()
    {
        Task* t = nullptr;

        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        Error_t errorCode = HttpUtilz::DataErrorIntoHttpCode( statusCode );
        if ( errorCode == Data::None )
        {
            try {
                t = new Task( m_parser->BytestreamIntoTask( reply->readAll() ) );
            } catch (...) {
                errorCode = Data::InvalidFormat;
            }
        }

        emit retVal->responseGetTask( t, errorCode );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
    return retVal;
}


AsyncDataLyr_TaskResponse* AsyncDataLyr_TaskHttp::createTask( const Task& newTask )
{
    AsyncDataLyr_TaskResponse* retVal = new AsyncDataLyr_TaskResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2").arg( m_url,
                                          m_resourceCollection ) );

    QNetworkReply* reply = m_networkAccess->post( request,
                                                  m_parser->TaskIntoBytestream( newTask )  );

    auto handleResponse = [this, retVal, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit retVal-> responseCreateTask( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
    return retVal;
}


AsyncDataLyr_TaskResponse* AsyncDataLyr_TaskHttp::changeTask( const Task& changedTask )
{
    AsyncDataLyr_TaskResponse* retVal = new AsyncDataLyr_TaskResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( changedTask.getId() ) ) );

    QNetworkReply* reply = m_networkAccess->put( request,
                                                 m_parser->TaskIntoBytestream( changedTask ) );

    auto handleResponse = [this, retVal, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit retVal->responseChangeTask( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
    return retVal;
}


AsyncDataLyr_TaskResponse* AsyncDataLyr_TaskHttp::deleteTask( const UniqueId taskId )
{
    AsyncDataLyr_TaskResponse* retVal = new AsyncDataLyr_TaskResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( taskId ) ) );

    QNetworkReply* reply = m_networkAccess->deleteResource( request );

    auto handleResponse = [this, retVal, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit retVal->responseDeleteTask( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
    return retVal;
}


void AsyncDataLyr_TaskHttp::onNetworkReply( QNetworkReply* reply )
{

    reply->deleteLater();
}

