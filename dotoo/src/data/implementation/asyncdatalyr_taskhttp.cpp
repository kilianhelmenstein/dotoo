#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "asyncdatalyr_taskhttp.h"
#include "models/interface/task.h"
#include "modelparser/interface/bytestreamtaskparser.h"



using namespace Dotoo;
using namespace Dotoo::Data;
using namespace Dotoo::ModelParser;



AsyncDataLyr_TaskHttp::AsyncDataLyr_TaskHttp( const QString& url,
                                              const QString& resourceCollection,
                                              const ModelParser::BytestreamTaskParser& parser)
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
        QList<Task>* allTasks = new QList<Task>( m_parser.BytestreamIntoTaskList( reply->readAll() ) );
        emit responseGetAllTasks( allTasks );
    };

    connect( reply, &QNetworkReply::readyRead, handleResponse );
}


void AsyncDataLyr_TaskHttp::getTask( UniqueId taskId )
{
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( taskId ) ) );

    QNetworkReply* reply = m_networkAccess->get( request );

    auto handleResponse = [&]()
    {
        Task* t = new Task( m_parser.BytestreamIntoTask( reply->readAll() ) );
        emit responseGetTask( t );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
}


void AsyncDataLyr_TaskHttp::createTask( const Task& newTask )
{
    QNetworkRequest request;
    request.setUrl( QString("%1/%2").arg( m_url,
                                          m_resourceCollection ) );

    QNetworkReply* reply = m_networkAccess->post( request,
                                                  m_parser.TaskIntoBytestream( newTask )  );

    auto handleResponse = [&]()
    {
        emit responseCreateTask( None );
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
                                                 m_parser.TaskIntoBytestream( changedTask ) );

    auto handleResponse = [&]()
    {
        emit responseCreateTask( None );
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

    auto handleResponse = [&]()
    {
        emit responseCreateTask( None );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
}


void AsyncDataLyr_TaskHttp::onNetworkReply( QNetworkReply* reply )
{

    reply->deleteLater();
}

