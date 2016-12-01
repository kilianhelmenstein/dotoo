#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QList>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

#include "datalyr_personsql.h"
#include "models/interface/person.h"
#include "models/interface/types/persontypes.h"
#include "data/utils/sqlrequest.h"



using namespace Dotoo;
using namespace Dotoo::Data;


const QLatin1String DataLyr_PersonSql::SQLDriverSpec = QLatin1String( "QSQLITE" );



DataLyr_PersonSql::DataLyr_PersonSql( const QString& databaseConnection,
                                      const QString& databaseName,
                                      const QString& tableName )
    : m_databaseConnection( databaseConnection ),
      m_databaseName( databaseName ),
      m_tableName( tableName )
{
    // If necessary, add database:
    if ( !QSqlDatabase::contains( m_databaseConnection ) )
    {
        QSqlDatabase::addDatabase( SQLDriverSpec, m_databaseConnection );
    }

    /* Check whether table for persons exists. If not, create a new table: */
    QSqlDatabase db( QSqlDatabase::database( m_databaseConnection ) );
    db.setDatabaseName( m_databaseName );
    db.open();

    if ( !db.tables().contains( m_tableName ) )
    {
        /* Person table is not existing. Create it: */
        SqlRequest sqlRequest;
        QList<SqlRequest::SqlColumnSpec> columns;
        columns << SqlRequest::SqlColumnSpec( "id", SqlRequest::Int, 0, SqlRequest::PrimaryKey )
                << SqlRequest::SqlColumnSpec( "name", SqlRequest::VarChar )
                << SqlRequest::SqlColumnSpec( "forename", SqlRequest::VarChar )
                << SqlRequest::SqlColumnSpec( "comment", SqlRequest::VarChar );
        sqlRequest.createTable( m_tableName, columns ).end();

        QSqlQuery dbQuery( sqlRequest.toString(), db );
        dbQuery.exec( sqlRequest.toString() );
    }

    db.close();
}


DataLyr_PersonSql::~DataLyr_PersonSql()
{
}


QList<Person> DataLyr_PersonSql::getAllPersons() throw(Error_t)
{
    QSqlDatabase db( QSqlDatabase::database( m_databaseConnection ) );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest.selectAll( m_tableName ).end();

    QSqlQuery dbQuery( sqlRequest.toString(), db );
    db.close();

    QList<Person> result;
    while ( dbQuery.next() )
    {
        result.append( Person( dbQuery.value("id").toInt(),
                               PersonName_t(
                                   dbQuery.value("forename").toString(),
                                   dbQuery.value("name").toString() ),
                               dbQuery.value("comment").toString() ) );
    }

    return result;
}


Person DataLyr_PersonSql::getPerson( const UniqueId personId ) throw(Error_t)
{
    QSqlDatabase db( QSqlDatabase::database( m_databaseConnection ) );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest
            .selectAll( m_tableName )
            .where( "id", SqlRequest::Equal, QString::number(personId) )
            .end();

    QSqlQuery dbQuery( sqlRequest.toString(), db );
    db.close();

    if ( dbQuery.next() )
    {
        return Person( dbQuery.value("id").toInt(),
                       PersonName_t(
                           dbQuery.value("name").toString(),
                           dbQuery.value("forename").toString() ),
                       dbQuery.value("comment").toString() );
    } else
    {
        throw ( NotFound );
    }
}


void DataLyr_PersonSql::createPerson( const Person& newPerson ) throw(Error_t)
{
    QSqlDatabase db( QSqlDatabase::database( m_databaseConnection ) );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest
            .insertInto( m_tableName,
                         QStringList()
                         << "name"
                         << "forename"
                         << "comment",
                         QStringList()
                         << newPerson.getName().name
                         << newPerson.getName().forename
                         << newPerson.getComment() )
            .end();
    QSqlQuery dbQuery( sqlRequest.toString(), db );

    db.close();
}


void DataLyr_PersonSql::changePerson( const Person& changedPerson ) throw(Error_t)
{
    QSqlDatabase db( QSqlDatabase::database( m_databaseConnection ) );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest
            .update( m_tableName,
                     QStringList()
                     << "name"
                     << "forename"
                     << "comment",
                     QStringList()
                     << changedPerson.getName().name
                     << changedPerson.getName().forename
                     << changedPerson.getComment() )
            .where( "id", SqlRequest::Equal, QString::number( changedPerson.getId() ) )
            .end();

    QSqlQuery dbQuery( sqlRequest.toString(), db );
    db.close();
}


void DataLyr_PersonSql::deletePerson( const UniqueId personId ) throw(Error_t)
{
    QSqlDatabase db( QSqlDatabase::database( m_databaseConnection ) );
    db.setDatabaseName( m_databaseName );
    db.open();

    SqlRequest sqlRequest;
    sqlRequest
            .deleteRecords( m_tableName )
            .where( "id", SqlRequest::Equal, QString::number(personId) )
            .end();

    QSqlQuery dbQuery( sqlRequest.toString(), db );
    qDebug() << sqlRequest.toString();
    qDebug() << dbQuery.lastError();
    db.close();
}
