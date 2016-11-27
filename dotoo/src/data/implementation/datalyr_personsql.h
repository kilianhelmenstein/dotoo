#ifndef DATALYR_PERSONSQL_H
#define DATALYR_PERSONSQL_H

#include <memory>
#include <QString>

#include "project/libsymbolsexport.h"
#include "data/interface/datalyr_person.h"


class QSqlQuery;

namespace Dotoo {
namespace Data {


/*!
 * \brief   The DataLyr_PersonSql class is an implementation of the DataLyr_Person interface
 *          using a SQL database for accessing and storing persistence data.
 */
class LIB_EXPORT DataLyr_PersonSql : public DataLyr_Person
{
private:
    static const QLatin1String SQLDriverSpec;


public:
    DataLyr_PersonSql( const QString& databaseName,
                       const QString& tableName );
    virtual ~DataLyr_PersonSql();

    QList<Person> getAllPersons() throw(Error_t);
    Person getPerson( const UniqueId personId ) throw(Error_t);
    void createPerson( const Person& newPerson ) throw(Error_t);
    void changePerson( const Person& changedPerson ) throw(Error_t);
    void deletePerson( const UniqueId personId ) throw(Error_t);


private:
    std::shared_ptr<QSqlQuery> getDatabaseConnection();

private:
    const QString m_databaseName;
    const QString m_tableName;
};


} // namespace Data
} // namespace Dotoo

#endif // DATALYR_PERSONSQL_H
