#ifndef DATALYR_TASKSQL_H
#define DATALYR_TASKSQL_H

#include <memory>
#include <QString>

#include "project/libsymbolsexport.h"
#include "data/interface/datalyr_task.h"


class QSqlQuery;

namespace Dotoo {
namespace Data {


/*!
 * \brief   The DataLyr_TaskSql class is an implementation of the DataLyr_Task interface
 *          using a SQL database for accessing and storing persistence data.
 */
class LIB_EXPORT DataLyr_TaskSql : public DataLyr_Task
{
private:
    static const QLatin1String SQLDriverSpec;


public:
    DataLyr_TaskSql( const QString databaseConnection,
                     const QString& databaseName,
                     const QString& tableName );
    virtual ~DataLyr_TaskSql();

    QList<Task> getAllTasks() throw(Error_t);
    Task getTask( const UniqueId taskId ) throw(Error_t);
    void createTask( const Task& newTask ) throw(Error_t);
    void changeTask( const Task& changedTask ) throw(Error_t);
    void deleteTask( const UniqueId taskId ) throw(Error_t);


private:
    std::shared_ptr<QSqlQuery> getDatabaseConnection();

private:
    const QString m_databaseConnection;
    const QString m_databaseName;
    const QString m_tableName;
};

} // namespace Data
} // namespace Dotoo


#endif // DATALYR_TASKSQL_H
