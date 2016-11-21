/********************* Includes *********************/

#include <QStringList>
#include <QMap>

#include "sqlrequest.h"



/******************** Namespaces ********************/

using namespace Persistence;



/************** Static Varialbes Init ***************/

/* Column Selector: */
const QLatin1String SqlRequest::SqlKeyword_Select = QLatin1String( "select " );

const QLatin1String SqlRequest::SqlSelection_All = QLatin1String( "* " );
const QLatin1String SqlRequest::SqlSelection_Distinct = QLatin1String( "distinct " );

/* Table Selector: */
const QLatin1String SqlRequest::SqlKeyword_From = QLatin1String( "from " );

/* Conditioning: */
const QLatin1String SqlRequest::SqlKeyword_Where = QLatin1String( "where " );

/* Operators: */
const QLatin1String SqlRequest::SqlOperator_Equal = QLatin1String( "= " );
const QLatin1String SqlRequest::SqlOperator_NotEqual = QLatin1String( "<> " );
const QLatin1String SqlRequest::SqlOperator_GreaterThan = QLatin1String( "> " );
const QLatin1String SqlRequest::SqlOperator_LessThan = QLatin1String( "< " );
const QLatin1String SqlRequest::SqlOperator_GreaterThanOrEqual = QLatin1String( ">= " );
const QLatin1String SqlRequest::SqlOperator_LessThanOrEqual = QLatin1String( "<= " );
const QLatin1String SqlRequest::SqlOperator_Between = QLatin1String( "between " );
const QLatin1String SqlRequest::SqlOperator_Like = QLatin1String( "like " );
const QLatin1String SqlRequest::SqlOperator_In = QLatin1String( "in " );

const QLatin1String SqlRequest::SqlOperator_And = QLatin1String( "and " );
const QLatin1String SqlRequest::SqlOperator_Or = QLatin1String( "or " );

/* Ordering result: */
const QLatin1String SqlRequest::SqlKeyword_OrderBy = QLatin1String( "order by " );
const QLatin1String SqlRequest::SqlOrder_Ascending = QLatin1String( "asc" );
const QLatin1String SqlRequest::SqlOrder_Descending = QLatin1String( "desc " );

/* Create new record: */
const QLatin1String SqlRequest::SqlKeyword_InsertInto = QLatin1String( "insert into " );
const QLatin1String SqlRequest::SqlKeyword_Values = QLatin1String( "values " );

/* Manipulate data: */
const QLatin1String SqlRequest::SqlKeyword_Update = QLatin1String( "update " );
const QLatin1String SqlRequest::SqlKeyword_Set = QLatin1String( "set " );

/* Delete data: */
const QLatin1String SqlRequest::SqlKeyword_DeleteFrom = QLatin1String( "delete from" );

/* Some special SqlRequest::Sql characters: */
const QLatin1String SqlRequest::SqlSyntax_Assignment = QLatin1String( "=" );
const QLatin1String SqlRequest::SqlSyntax_ValuesOpener = QLatin1String( "(" );
const QLatin1String SqlRequest::SqlSyntax_ValuesCloser = QLatin1String( ")" );
const QLatin1String SqlRequest::SqlSyntax_ListingSeperator = QLatin1String( "," );
const QLatin1String SqlRequest::SqlSyntax_EORequest = QLatin1String( ";" );



SqlRequest::SqlRequest()
{}


SqlRequest::SqlRequest( const SqlRequest& other )
    : m_sqlRequest( other.m_sqlRequest )
{
}


SqlRequest& SqlRequest::operator=( const SqlRequest& other )
{
    QString* temp = m_sqlRequest.get();
    m_sqlRequest.reset( new QString( *(other.m_sqlRequest) ) );
    delete temp;

    return *this;
}


void SqlRequest::swap( SqlRequest& other )
{
    m_sqlRequest.swap( other.m_sqlRequest );
}



/* Forming SQL Request: */

SqlRequest& SqlRequest::clear()
{
    m_sqlRequest->clear();
    return *this;
}

SqlRequest& SqlRequest::selectAll( const QString& tableName )
{
    return select( SqlSelection_All, tableName );
}

SqlRequest& SqlRequest::select( const QString& columnName, const QString& tableName )
{
    clear();
    m_sqlRequest->append( SqlKeyword_Select
                          + ParseName(columnName)
                          + SqlKeyword_From
                          + ParseName(tableName) );

    return *this;
}

SqlRequest& SqlRequest::select( const QStringList& columnNames, const QString& tableName )
{
    clear();
    m_sqlRequest->append( SqlKeyword_Select
                          + ParseName(columnNames.join(SqlSyntax_ListingSeperator))
                          + SqlKeyword_From
                          + ParseName(tableName) );
    return *this;
}


SqlRequest& SqlRequest::selectAllDistinct( const QString& tableName )
{
    return selectDistinct( SqlSelection_All, tableName );
}


SqlRequest& SqlRequest::selectDistinct( const QString& columnName, const QString& tableName )
{
    clear();
    m_sqlRequest->append( SqlKeyword_Select
                          + SqlSelection_Distinct
                          + ParseName(columnName) + SqlKeyword_From + ParseName(tableName) );
    return *this;
}

SqlRequest& SqlRequest::selectDistinct( const QStringList& columnNames, const QString& tableName )
{
    clear();
    m_sqlRequest->append( SqlKeyword_Select
                          + SqlSelection_Distinct
                          + ParseName(columnNames.join(SqlSyntax_ListingSeperator))
                          + SqlKeyword_From
                          + ParseName(tableName) );
    return *this;
}


SqlRequest& SqlRequest::where( const QString& columnName,
                               const SqlComparisionOperator comparisionOp,
                               const QString& value )
{
    m_sqlRequest->append( SqlKeyword_Where
                          + ParseName(columnName)
                          + GetComparisionOperator(comparisionOp)
                          + value );
    return *this;
}


SqlRequest& SqlRequest::andCond( const QString& columnName,
                                 const SqlComparisionOperator comparisionOp,
                                 const QString& value )
{
    m_sqlRequest->append( SqlOperator_And
                          + ParseName(columnName)
                          + GetComparisionOperator(comparisionOp)
                          + value );
    return *this;
}

SqlRequest& SqlRequest::orCond( const QString& columnName,
                                const SqlComparisionOperator comparisionOp,
                                const QString& value )
{
    m_sqlRequest->append( SqlOperator_Or
                          + ParseName(columnName)
                          + GetComparisionOperator(comparisionOp)
                          + value );
    return *this;
}


SqlRequest& SqlRequest::orderBy( const QString& columnname,
                                 const SqlOrder order )
{
    m_sqlRequest->append( SqlKeyword_OrderBy
                          + ParseName(columnname)
                          + GetOrder(order) );
    return *this;
}


SqlRequest& SqlRequest::insertInto( const QString& tableName,
                                    const QStringList& values )
{
    m_sqlRequest->append( SqlKeyword_InsertInto
                          + ParseName(tableName)
                          + SqlKeyword_Values
                          + SqlSyntax_ValuesOpener
                          + values.join(SqlSyntax_ListingSeperator)
                          + SqlSyntax_ValuesCloser );
    return *this;
}

SqlRequest& SqlRequest::insertInto( const QString& tableName,
                                    const QStringList& columnNames,
                                    const QStringList& values )
{
    m_sqlRequest->append( SqlKeyword_InsertInto
                          + ParseName(tableName)
                          + SqlSyntax_ValuesOpener
                          + columnNames.join(SqlSyntax_ListingSeperator)
                          + SqlSyntax_ValuesCloser
                          + SqlKeyword_Values
                          + SqlSyntax_ValuesOpener
                          + values.join(SqlSyntax_ListingSeperator)
                          + SqlSyntax_ValuesCloser );
    return *this;
}


SqlRequest& SqlRequest::update( const QString tableName,
                                const QStringList& columnNames,
                                const QStringList& values )
{
    if ( columnNames.size() == values.size() )
    {
        m_sqlRequest->append( SqlKeyword_Update
                              + ParseName(tableName)
                              + SqlKeyword_Set );

        /* Insert columnName/value pairs: */
        for ( int i=0 ; i<columnNames.size() ; i++ )
        {
            if ( i != 0 ) { m_sqlRequest->append( SqlSyntax_ListingSeperator ); }
            m_sqlRequest->append( ParseName(columnNames.at(i))
                                  + SqlSyntax_Assignment
                                  + ParseName(values.at(i) ));
        }
    }
    return *this;
}


SqlRequest& SqlRequest::deleteRecords( const QString tableName )
{
    m_sqlRequest->append( SqlKeyword_DeleteFrom
                          + ParseName(tableName) );
    return *this;
}


SqlRequest& SqlRequest::end()
{
    m_sqlRequest->append( SqlSyntax_EORequest );
    return *this;
}



QString SqlRequest::ParseName( const QString& fieldName )
{
    return fieldName + QLatin1Char(' ');
}


QLatin1String SqlRequest::GetComparisionOperator( const SqlComparisionOperator comparisionOp )
{
    switch ( comparisionOp )
    {
    case NotEqual:
        return SqlOperator_NotEqual;
    case GreaterThan:
        return SqlOperator_GreaterThan;
    case LessThan:
        return SqlOperator_LessThan;
    case GreaterThanOrEqual:
        return SqlOperator_GreaterThanOrEqual;
    case LessThanOrEqual:
        return SqlOperator_LessThanOrEqual;
    case Between:
        return SqlOperator_Between;
    case Like:
        return SqlOperator_Like;
    case In:
        return SqlOperator_In;
    case Equal:
    default:
        return SqlOperator_Equal;
    }
}


QLatin1String SqlRequest::GetOrder( const SqlOrder order )
{
    switch ( order )
    {
    case Ascending:
        return SqlOrder_Ascending;
    case Descending:
    default:
        return SqlOrder_Ascending;
    }
}

