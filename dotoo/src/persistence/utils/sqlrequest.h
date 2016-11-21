#ifndef SQLREQUEST_H
#define SQLREQUEST_H

/********************* Includes *********************/

#include <memory>

#include <QString>



/******************** Namespaces ********************/

namespace Persistence {



/*********************** Class **********************/

/*!
 * \brief   The SqlRequest class is a convinience class for building sql requests in a call-the-method
 *          manner. (For adding keywords you have to call methods instead of adding strings.)
 *
 *          See SQL specification for details.
 */
class SqlRequest
{
public:
/***************** Static Varialbes *****************/

    /* Column Selector: */
    static const QLatin1String SqlKeyword_Select;

    static const QLatin1String SqlSelection_All;
    static const QLatin1String SqlSelection_Distinct;

    /* Table Selector: */
    static const QLatin1String SqlKeyword_From;

    /* Conditioning: */
    static const QLatin1String SqlKeyword_Where;

    /* Operators: */
    static const QLatin1String SqlOperator_Equal;
    static const QLatin1String SqlOperator_NotEqual;
    static const QLatin1String SqlOperator_GreaterThan;
    static const QLatin1String SqlOperator_LessThan;
    static const QLatin1String SqlOperator_GreaterThanOrEqual;
    static const QLatin1String SqlOperator_LessThanOrEqual;
    static const QLatin1String SqlOperator_Between;
    static const QLatin1String SqlOperator_Like;
    static const QLatin1String SqlOperator_In;

    static const QLatin1String SqlOperator_And;
    static const QLatin1String SqlOperator_Or;

    /* Ordering result: */
    static const QLatin1String SqlKeyword_OrderBy;
    static const QLatin1String SqlOrder_Ascending;
    static const QLatin1String SqlOrder_Descending;

    /* Create new record: */
    static const QLatin1String SqlKeyword_InsertInto;
    static const QLatin1String SqlKeyword_Values;

    /* Manipulate data: */
    static const QLatin1String SqlKeyword_Update;
    static const QLatin1String SqlKeyword_Set;

    /* Delete data: */
    static const QLatin1String SqlKeyword_DeleteFrom;

    /* Some special SQL characters: */
    static const QLatin1String SqlSyntax_Assignment;
    static const QLatin1String SqlSyntax_ValuesOpener;
    static const QLatin1String SqlSyntax_ValuesCloser;
    static const QLatin1String SqlSyntax_ListingSeperator;
    static const QLatin1String SqlSyntax_EORequest;

    typedef enum {
        Equal,
        NotEqual,
        GreaterThan,
        LessThan,
        GreaterThanOrEqual,
        LessThanOrEqual,
        Between,
        Like,
        In
    } SqlComparisionOperator;

    typedef enum {
        Ascending,
        Descending
    } SqlOrder;


public:
    SqlRequest();
    SqlRequest( const SqlRequest& other );

    SqlRequest& operator=( const SqlRequest& other );

    void swap( SqlRequest& other );


    /* Forming SQL Request: */
    SqlRequest& clear();

    SqlRequest& selectAll( const QString& tableName );
    SqlRequest& select( const QString& columnName, const QString& tableName );
    SqlRequest& select( const QStringList& columnNames, const QString& tableName );

    SqlRequest& selectAllDistinct( const QString& tableName );
    SqlRequest& selectDistinct( const QString& columnName, const QString& tableName );
    SqlRequest& selectDistinct( const QStringList& columnNames, const QString& tableName );

    SqlRequest& where( const QString& columnName,
                       const SqlComparisionOperator comparisionOp,
                       const QString& value );

    SqlRequest& andCond( const QString& columnName,
                         const SqlComparisionOperator comparisionOp,
                         const QString& value );
    SqlRequest& orCond( const QString& columnName,
                        const SqlComparisionOperator comparisionOp,
                        const QString& value );

    SqlRequest& orderBy( const QString& columnname,
                         const SqlOrder );

    SqlRequest& insertInto( const QString& tableName,
                            const QStringList& values );
    SqlRequest& insertInto( const QString& tableName,
                            const QStringList &columnNames,
                            const QStringList &values );

    SqlRequest& update( const QString tableName,
                        const QStringList &columnNames,
                        const QStringList &values);

    SqlRequest& deleteRecords( const QString tableName );

    SqlRequest& end();



private:
    /*!
     * \brief   Adapts given (column or table) name for sql request rules of this class.
     *          (Currently just appending a space character to avoid syntax errors.)
     *
     * \return  Adapted name.
     */
    static QString ParseName( const QString& fieldName );
    static QLatin1String GetComparisionOperator( const SqlComparisionOperator comparisionOp );
    static QLatin1String GetOrder( const SqlOrder order );


private:
    std::shared_ptr<QString> m_sqlRequest;
};


} // namespace Persistence

#endif // SQLREQUEST_H
