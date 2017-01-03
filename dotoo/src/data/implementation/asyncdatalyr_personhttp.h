#ifndef ASYNCDATALYR_PERSONHTTP_H
#define ASYNCDATALYR_PERSONHTTP_H


#include "data/interface/asyncdatalyr_person.h"


class QNetworkAccessManager;
class QNetworkReply;


namespace Dotoo {

namespace ModelParser {
class BytestreamPersonParser;
}


namespace Data {



class LIB_EXPORT AsyncDataLyr_PersonHttp : public AsyncDataLyr_Person
{
    Q_OBJECT
public:
    AsyncDataLyr_PersonHttp( const QString& url,
                           const QString& resourceCollection,
                           ModelParser::BytestreamPersonParser* parser );
    virtual ~AsyncDataLyr_PersonHttp();

    AsyncDataLyr_PersonResponse* getAllPersons();
    AsyncDataLyr_PersonResponse* getPerson( const UniqueId personId );
    AsyncDataLyr_PersonResponse* createPerson( const Person& newPerson );
    AsyncDataLyr_PersonResponse* changePerson( const Person& changedPerson );
    AsyncDataLyr_PersonResponse* deletePerson( const UniqueId personId );

private slots:
    void onNetworkReply( QNetworkReply* reply );

private:
    QString m_url;                                  /*!< URL that receives the network requests. */
    QString m_resourceCollection;                   /*!< Used resource collection for gettings Persons */
    ModelParser::BytestreamPersonParser* m_parser;  /*!< Used object to parse raw data into Person instances. */

    QNetworkAccessManager* m_networkAccess;         /*!< Used to access network and perfrom http requests. */
};


} // namespace Data
} // namespace Dotoo


#endif // ASYNCDATALYR_PERSONHTTP_H
