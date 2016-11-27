#ifndef SQLREQUEST_H
#define SQLREQUEST_H

/********************* Includes *********************/

#include "project/libsymbolsexport.h"


class QString;
class QStringList;



/*********************** Class **********************/

/*!
 * \brief   The SqlRequest class is a convinience class for building sql requests and preventing
 *          sql-syntax errors.
 *
 *          This class allows you to build your sql requests by calling the specific
 *          method with proper parameter list.
 *
 *          See SQL specification for details.
 */
class LIB_EXPORT SqlRequest
{
public:
    /***************** Static Varialbes *****************/

    static const QLatin1String SqlKeyWord_CreateTable;
    static const QLatin1String SqlConstraint_NotNull;
    static const QLatin1String SqlConstraint_Unique;
    static const QLatin1String SqlConstraint_PrimaryKey;
    static const QLatin1String SqlConstraint_ForeignKey;
    static const QLatin1String SqlConstraint_Check;
    static const QLatin1String SqlConstraint_AutoIncrement;

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

    static const QLatin1String SqlDatatype_Char;
    static const QLatin1String SqlDatatype_VarChar;
    static const QLatin1String SqlDatatype_Int;



/********************* Typedefs *********************/

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

    typedef enum {
        Char,
        VarChar,
        Int
    } SqlDatatype;

    typedef enum {
        NoConstraint,
        NotNull,
        Unique,
        PrimaryKey,
        ForeignKey,
        Check,
        AutoIncrement
    } SqlConstraint;

    typedef struct _SqlColumnSpec {
        _SqlColumnSpec( QString columnName,
                        SqlDatatype datatype,
                        int fieldSize=255,
                        SqlConstraint constraint=NoConstraint )
            : columnName( columnName ),
              datatype( datatype ),
              fieldSize( fieldSize ),
              constraint( constraint )
        {}

        QString columnName;
        SqlDatatype datatype;
        int fieldSize;
        SqlConstraint constraint;
    } SqlColumnSpec;


public:
    SqlRequest();
    SqlRequest( const SqlRequest& other );

    ~SqlRequest();

    SqlRequest& operator=( const SqlRequest& other );

    void swap( SqlRequest& other );

    QString toString() const;

    /* Forming SQL Request: */
    SqlRequest& clear();

    SqlRequest& createTable( const QString& tableName,
                             const QList<SqlColumnSpec>& columnSpecifiers );

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
                            const QStringList &values );
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

    static QStringList ParseValueList( const QStringList& values );

    /*!
     * \brief   Returns the selected comparision operator in sql-valid string format.
     *
     * \param   const SqlComparisionOperator comparisionOp      Operator selection.
     *
     * \return  QString     Selected sql-comp. as string.
     */
    static QString GetComparisionOperator( const SqlComparisionOperator comparisionOp );

    /*!
     * \brief   Returns the selected sql-record-order in sql-valid string format.
     *
     * \param   const SqlOrder order        Selected order.
     *
     * \return  QString     Selected order in string format.
     */
    static QString GetOrder( const SqlOrder order );

    /*!
     * \brief   Returns the selected sql-column-specification (for creating new tables)
     *          in sql-valid string format.
     *
     * \param   const SqlColumnSpec spec    Column spec. for a new table.
     *
     * \return  QString     Column specification in string format.
     */
    static QString GetColumnSpec( const SqlColumnSpec spec );

private:
    QString* m_sqlRequest;
};

#endif // SQLREQUEST_H
