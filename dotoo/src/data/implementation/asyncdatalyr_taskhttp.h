#ifndef ASYNCDATALYR_TASKHTTP_H
#define ASYNCDATALYR_TASKHTTP_H

#include "data/interface/asyncdatalyr_task.h"


class QNetworkAccessManager;
class QNetworkReply;


namespace Dotoo {

namespace ModelParser {
class BytestreamTaskParser;
}


namespace Data {



class LIB_EXPORT AsyncDataLyr_TaskHttp : public AsyncDataLyr_Task
{
    Q_OBJECT
public:
    AsyncDataLyr_TaskHttp( const QString& url,
                           const QString& resourceCollection,
                           ModelParser::BytestreamTaskParser* parser );
    virtual ~AsyncDataLyr_TaskHttp();

    AsyncDataLyr_TaskResponse* getAllTasks();
    AsyncDataLyr_TaskResponse* getTask( const UniqueId taskId );
    AsyncDataLyr_TaskResponse* createTask( const Task& newTask );
    AsyncDataLyr_TaskResponse* changeTask( const Task& changedTask );
    AsyncDataLyr_TaskResponse* deleteTask( const UniqueId taskId );

private slots:
    void onNetworkReply( QNetworkReply* reply );

private:
    QString m_url;                          /*!< URL that receives the network requests. */
    QString m_resourceCollection;           /*!< Used resource collection for gettings tasks */
    ModelParser::BytestreamTaskParser* m_parser; /*!< Used object to parse raw data into Task instances. */

    QNetworkAccessManager* m_networkAccess; /*!< Used to access network and perfrom http requests. */
};


} // namespace Data
} // namespace Dotoo

#endif // ASYNCDATALYR_TASKHTTP_H
