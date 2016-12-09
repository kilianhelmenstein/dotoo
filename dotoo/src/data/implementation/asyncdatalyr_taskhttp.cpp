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


void AsyncDataLyr_TaskHttp::getAllTasks()
{
    QNetworkRequest request;
    request.setUrl( QString("%1/%2").arg( m_url, m_resourceCollection ) );
    QNetworkReply* reply = m_networkAccess->get( request );

    auto handleResponse = [&]()
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

        emit responseGetAllTasks( allTasks, errorCode );
    };

    connect( reply, &QNetworkReply::readyRead, handleResponse );
}


void AsyncDataLyr_TaskHttp::getTask( const UniqueId taskId )
{
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( taskId ) ) );

    QNetworkReply* reply = m_networkAccess->get( request );

    auto handleResponse = [&]()
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

        emit responseGetTask( t, errorCode );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
}


void AsyncDataLyr_TaskHttp::createTask( const Task& newTask )
{
    QNetworkRequest request;
    request.setUrl( QString("%1/%2").arg( m_url,
                                          m_resourceCollection ) );

    QNetworkReply* reply = m_networkAccess->post( request,
                                                  m_parser->TaskIntoBytestream( newTask )  );

    auto handleResponse = [this, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit responseCreateTask( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
}


void AsyncDataLyr_TaskHttp::changeTask( const Task& changedTask )
{
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( changedTask.getId() ) ) );

    QNetworkReply* reply = m_networkAccess->put( request,
                                                 m_parser->TaskIntoBytestream( changedTask ) );

    auto handleResponse = [this, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit responseCreateTask( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
}


void AsyncDataLyr_TaskHttp::deleteTask( const UniqueId taskId )
{
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( taskId ) ) );

    QNetworkReply* reply = m_networkAccess->deleteResource( request );

    auto handleResponse = [this, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit responseCreateTask( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
}


void AsyncDataLyr_TaskHttp::onNetworkReply( QNetworkReply* reply )
{

    reply->deleteLater();
}

