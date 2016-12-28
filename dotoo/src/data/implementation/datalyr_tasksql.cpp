#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDate>
#include <QList>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

#include "datalyr_tasksql.h"
#include "models/interface/task.h"
#include "models/interface/types/tasktypes.h"
#include "data/utils/sqlrequest.h"



using namespace Dotoo;
using namespace Dotoo::Data;


const QLatin1String DataLyr_TaskSql::SQLDriverSpec = QLatin1String( "QSQLITE" );



DataLyr_TaskSql::DataLyr_TaskSql( const QString databaseConnection,
                                  const QString& databaseName,
                                  const QString& tableName )
    : m_databaseConnection( databaseConnection ),
      m_databaseName( databaseName ),
      m_tableName( tableName ),
      m_database( nullptr )
{
    // If necessary, add database:
    if ( !QSqlDatabase::contains( m_databaseConnection ) )
    {
          m_database = new QSqlDatabase( QSqlDatabase::addDatabase( SQLDriverSpec, m_databaseConnection )) ;
    } else
    {
        m_database = new QSqlDatabase( QSqlDatabase::database( m_databaseConnection ) );
    }

    /* Check whether table for tasks exists. If not, create a new table: */
    m_database->setDatabaseName( m_databaseName );
    m_database->open();

    if ( !m_database->tables().contains( m_tableName ) )
    {
        /* Task table is not existing. Create it: */
        SqlRequest sqlRequest;
        QList<SqlRequest::SqlColumnSpec> columns;
        columns << SqlRequest::SqlColumnSpec( "id", SqlRequest::Int, 0, SqlRequest::PrimaryKey )
                << SqlRequest::SqlColumnSpec( "title", SqlRequest::VarChar )
                << SqlRequest::SqlColumnSpec( "is_done", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "responsible", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "creator", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "creation_date", SqlRequest::VarChar )
                << SqlRequest::SqlColumnSpec( "due_date", SqlRequest::VarChar )
                << SqlRequest::SqlColumnSpec( "priority", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "related_project", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "comment", SqlRequest::VarChar );
        sqlRequest.createTable( m_tableName, columns ).end();

        QSqlQuery dbQuery( *m_database );
        dbQuery.exec( sqlRequest.toString() );
    }
}


DataLyr_TaskSql::~DataLyr_TaskSql()
{
    m_database->close();
    QSqlDatabase::removeDatabase( m_databaseConnection );
    delete m_database;
}


QList<Task> DataLyr_TaskSql::getAllTasks() throw(Error_t)
{
    SqlRequest sqlRequest;
    sqlRequest.selectAll( m_tableName ).end();

    QSqlQuery dbQuery( *m_database );
    dbQuery.setForwardOnly( true );      // For performance reasons
    dbQuery.exec( sqlRequest.toString() );

    QList<Task> result;
    while ( dbQuery.next() )
    {
        result.append( Task( dbQuery.value("id").toInt(),
                             dbQuery.value("title").toString(),
                             dbQuery.value("is_done").toBool(),
                             dbQuery.value("responsible").toInt(),
                             dbQuery.value("creator").toInt(),
                             QDate::fromString( dbQuery.value("creation_date").toString() ),
                             QDate::fromString( dbQuery.value("due_date").toString() ),
                             dbQuery.value("priority").toInt(),
                             dbQuery.value("related_project").toInt(),
                             dbQuery.value("comment").toString()
                             ) );
    }

    return result;
}


Task DataLyr_TaskSql::getTask( const UniqueId taskId ) throw(Error_t)
{
    SqlRequest sqlRequest;
    sqlRequest
            .selectAll( m_tableName )
            .where( "id", SqlRequest::Equal, QString::number(taskId) )
            .end();

    QSqlQuery dbQuery( *m_database );
    dbQuery.setForwardOnly( true );
    dbQuery.exec( sqlRequest.toString() );

    if ( dbQuery.next() )
    {
        return Task( dbQuery.value("id").toInt(),
                     dbQuery.value("title").toString(),
                     dbQuery.value("is_done").toBool(),
                     dbQuery.value("responsible").toInt(),
                     dbQuery.value("creator").toInt(),
                     QDate::fromString( dbQuery.value("creation_date").toString() ),
                     QDate::fromString( dbQuery.value("due_date").toString() ),
                     dbQuery.value("priority").toInt(),
                     dbQuery.value("related_project").toInt(),
                     dbQuery.value("comment").toString()
                     );
    } else
    {
        throw ( NotFound );
    }
}


void DataLyr_TaskSql::createTask( const Task& newTask ) throw(Error_t)
{
    SqlRequest sqlRequest;
    sqlRequest
            .insertInto( m_tableName,
                         QStringList()
                         << "title"
                         << "is_done"
                         << "responsible"
                         << "creator"
                         << "creation_date"
                         << "due_date"
                         << "priority"
                         << "related_project"
                         << "comment",
                         QStringList()
                         << newTask.getTitle()
                         << QString::number( newTask.isDone() )
                         << QString::number( newTask.getResponsible() )
                         << QString::number( newTask.getCreator() )
                         << newTask.getCreationDate().toString()
                         << newTask.getDueDate().toString()
                         << QString::number( newTask.getPriority() )
                         << QString::number( newTask.getRelatedProject() )
                         << newTask.getComment() )
            .end();
    QSqlQuery dbQuery( *m_database );
    dbQuery.exec( sqlRequest.toString() );
}


void DataLyr_TaskSql::changeTask( const Task& changedTask ) throw(Error_t)
{
    SqlRequest sqlRequest;
    sqlRequest
            .update( m_tableName,
                     QStringList()
                     << "title"
                     << "is_done"
                     << "responsible"
                     << "creator"
                     << "creation_date"
                     << "due_date"
                     << "priority"
                     << "related_project"
                     << "comment",
                     QStringList()
                     << changedTask.getTitle()
                     << QString::number( changedTask.isDone() )
                     << QString::number( changedTask.getResponsible() )
                     << QString::number( changedTask.getCreator() )
                     << changedTask.getCreationDate().toString()
                     << changedTask.getDueDate().toString()
                     << QString::number( changedTask.getPriority() )
                     << QString::number( changedTask.getRelatedProject() )
                     << changedTask.getComment() )
            .where( "id", SqlRequest::Equal, QString::number(changedTask.getId()) )
            .end();

    QSqlQuery dbQuery( *m_database );
    dbQuery.exec( sqlRequest.toString() );
    qDebug() << dbQuery.lastError();
}


void DataLyr_TaskSql::deleteTask( const UniqueId taskId ) throw(Error_t)
{
    SqlRequest sqlRequest;
    sqlRequest
            .deleteRecords( m_tableName )
            .where( "id", SqlRequest::Equal, QString::number(taskId) )
            .end();

    QSqlQuery dbQuery( *m_database );
    dbQuery.exec( sqlRequest.toString() );
}
