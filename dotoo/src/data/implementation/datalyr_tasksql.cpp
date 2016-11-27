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



DataLyr_TaskSql::DataLyr_TaskSql( const QString& databaseName,
                                  const QString& tableName )
    : m_databaseName( databaseName ),
      m_tableName( tableName )
{
    /* Check whether table for tasks exists. If not, create a new table: */
    QSqlDatabase db = QSqlDatabase::addDatabase( SQLDriverSpec );
    db.setDatabaseName( m_databaseName );
    db.open();

    if ( !db.tables().contains( m_tableName ) )
    {
        /* Task table is not existing. Create it: */
        SqlRequest sqlRequest;
        QList<SqlRequest::SqlColumnSpec> columns;
        columns << SqlRequest::SqlColumnSpec( "id", SqlRequest::Int, 0, SqlRequest::PrimaryKey )
                << SqlRequest::SqlColumnSpec( "is_done", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "responsible", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "creator", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "creation_date", SqlRequest::VarChar )
                << SqlRequest::SqlColumnSpec( "due_date", SqlRequest::VarChar )
                << SqlRequest::SqlColumnSpec( "priority", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "related_project", SqlRequest::Int )
                << SqlRequest::SqlColumnSpec( "comment", SqlRequest::VarChar );
        sqlRequest.createTable( m_tableName, columns ).end();

        QSqlQuery dbQuery( sqlRequest.toString(), db );
        dbQuery.exec( sqlRequest.toString() );
    }

    db.close();
}


DataLyr_TaskSql::~DataLyr_TaskSql()
{
}


QList<Task> DataLyr_TaskSql::getAllTasks() throw(Error_t)
{
    QSqlDatabase db = QSqlDatabase::addDatabase( SQLDriverSpec );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest.selectAll( m_tableName ).end();

    QSqlQuery dbQuery( sqlRequest.toString(), db );
    db.close();

    QList<Task> result;
    while ( dbQuery.next() )
    {
        result.append( Task( dbQuery.value("id").toInt(),
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
    QSqlDatabase db = QSqlDatabase::addDatabase( SQLDriverSpec );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest
            .selectAll( m_tableName )
            .where( "id", SqlRequest::Equal, QString::number(taskId) )
            .end();

    QSqlQuery dbQuery( sqlRequest.toString(), db );
    db.close();

    if ( dbQuery.next() )
    {
        return Task( dbQuery.value("id").toInt(),
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
    QSqlDatabase db = QSqlDatabase::addDatabase( SQLDriverSpec );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest
            .insertInto( m_tableName,
                         QStringList()
                         << "is_done"
                         << "responsible"
                         << "creator"
                         << "creation_date"
                         << "due_date"
                         << "priority"
                         << "related_project"
                         << "comment",
                         QStringList()
                         << QString::number( newTask.isDone() )
                         << QString::number( newTask.getResponsible() )
                         << QString::number( newTask.getCreator() )
                         << newTask.getCreationDate().toString()
                         << newTask.getDueDate().toString()
                         << QString::number( newTask.getPriority() )
                         << QString::number( newTask.getRelatedProject() )
                         << newTask.getComment() )
            .end();
    QSqlQuery dbQuery( sqlRequest.toString(), db );

    db.close();
}


void DataLyr_TaskSql::changeTask( const Task& changedTask ) throw(Error_t)
{
    QSqlDatabase db = QSqlDatabase::addDatabase( SQLDriverSpec );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest
            .update( m_tableName,
                     QStringList()
                     << "is_done"
                     << "responsible"
                     << "creator"
                     << "creation_date"
                     << "due_date"
                     << "priority"
                     << "related_project"
                     << "comment",
                     QStringList()
                     << QString::number( changedTask.isDone() )
                     << QString::number( changedTask.getResponsible() )
                     << QString::number( changedTask.getCreator() )
                     << changedTask.getCreationDate().toString()
                     << changedTask.getDueDate().toString()
                     << QString::number( changedTask.getPriority() )
                     << QString::number( changedTask.getRelatedProject() )
                     << changedTask.getComment() )
            .end();

    QSqlQuery dbQuery( sqlRequest.toString(), db );
    db.close();
}


void DataLyr_TaskSql::deleteTask( const UniqueId taskId ) throw(Error_t)
{
    QSqlDatabase db = QSqlDatabase::addDatabase( SQLDriverSpec );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest
            .deleteRecords( m_tableName )
            .where( "id", SqlRequest::Equal, QString::number(taskId) )
            .end();

    QSqlQuery dbQuery( sqlRequest.toString(), db );
    qDebug() << sqlRequest.toString();
    qDebug() << dbQuery.lastError();
    db.close();
}
