#include "asyncdatalyr_personhttp.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "data/utils/http.h"
#include "models/interface/person.h"
#include "modelparser/interface/bytestreampersonparser.h"


using namespace Dotoo;
using namespace Dotoo::Data;
using namespace Dotoo::ModelParser;



AsyncDataLyr_PersonHttp::AsyncDataLyr_PersonHttp( const QString& url,
                                              const QString& resourceCollection,
                                              BytestreamPersonParser* parser)
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



AsyncDataLyr_PersonHttp::~AsyncDataLyr_PersonHttp()
{}


AsyncDataLyr_PersonResponse* AsyncDataLyr_PersonHttp::getAllPersons()
{
    AsyncDataLyr_PersonResponse* retVal = new AsyncDataLyr_PersonResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2").arg( m_url, m_resourceCollection ) );
    QNetworkReply* reply = m_networkAccess->get( request );

    auto handleResponse = [this, retVal, reply]()
    {
        QList<Person>* allPersons = nullptr;

        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        Error_t errorCode = HttpUtilz::DataErrorIntoHttpCode( statusCode );
        if ( errorCode == Data::None )
        {
            try {
                allPersons = new QList<Person>( m_parser->BytestreamIntoPersonList( reply->readAll() ) );
            } catch (...) {
                errorCode = Data::InvalidFormat;
            }
        }

        emit retVal-> responseGetAllPersons( allPersons, errorCode );
    };

    connect( reply, &QNetworkReply::readyRead, handleResponse );
    return retVal;
}


AsyncDataLyr_PersonResponse* AsyncDataLyr_PersonHttp::getPerson( const UniqueId personId )
{
    AsyncDataLyr_PersonResponse* retVal = new AsyncDataLyr_PersonResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( personId ) ) );

    QNetworkReply* reply = m_networkAccess->get( request );

    auto handleResponse = [this, retVal, reply]()
    {
        Person* t = nullptr;

        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        Error_t errorCode = HttpUtilz::DataErrorIntoHttpCode( statusCode );
        if ( errorCode == Data::None )
        {
            try {
                t = new Person( m_parser->BytestreamIntoPerson( reply->readAll() ) );
            } catch (...) {
                errorCode = Data::InvalidFormat;
            }
        }

        emit retVal->responseGetPerson( t, errorCode );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
    return retVal;
}


AsyncDataLyr_PersonResponse* AsyncDataLyr_PersonHttp::createPerson( const Person& newPerson )
{
    AsyncDataLyr_PersonResponse* retVal = new AsyncDataLyr_PersonResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2").arg( m_url,
                                          m_resourceCollection ) );

    QNetworkReply* reply = m_networkAccess->post( request,
                                                  m_parser->PersonIntoBytestream( newPerson )  );

    auto handleResponse = [this, retVal, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit retVal-> responseCreatePerson( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
    return retVal;
}


AsyncDataLyr_PersonResponse* AsyncDataLyr_PersonHttp::changePerson( const Person& changedPerson )
{
    AsyncDataLyr_PersonResponse* retVal = new AsyncDataLyr_PersonResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( changedPerson.getId() ) ) );

    QNetworkReply* reply = m_networkAccess->put( request,
                                                 m_parser->PersonIntoBytestream( changedPerson ) );

    auto handleResponse = [this, retVal, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit retVal->responseChangePerson( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
    return retVal;
}


AsyncDataLyr_PersonResponse* AsyncDataLyr_PersonHttp::deletePerson( const UniqueId personId )
{
    AsyncDataLyr_PersonResponse* retVal = new AsyncDataLyr_PersonResponse();
    QNetworkRequest request;
    request.setUrl( QString("%1/%2/%3").arg( m_url,
                                             m_resourceCollection,
                                             QString::number( personId ) ) );

    QNetworkReply* reply = m_networkAccess->deleteResource( request );

    auto handleResponse = [this, retVal, reply]()
    {
        const HttpUtilz::HttpStatusCode statusCode
                = static_cast<HttpUtilz::HttpStatusCode>(reply->attribute( QNetworkRequest::HttpStatusCodeAttribute ).toInt());
        emit retVal->responseDeletePerson( HttpUtilz::DataErrorIntoHttpCode( statusCode ) );
    };

    connect( reply, &QNetworkReply::finished, handleResponse );
    return retVal;
}


void AsyncDataLyr_PersonHttp::onNetworkReply( QNetworkReply* reply )
{

    reply->deleteLater();
}

