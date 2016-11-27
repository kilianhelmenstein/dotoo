#ifndef DATALYR_PERSON_H
#define DATALYR_PERSON_H

#include <QList>

#include "project/libsymbolsexport.h"
#include "models/interface/types/commontypes.h"



namespace Dotoo {

class Person;


namespace Data {


/*!
 * \brief   The PersonDataLyr class defines the layer for accessing
 *          the data of model type 'Person'.
 */
class LIB_EXPORT DataLyr_Person
{
public:
    /*!
     * \brief   Contains all possible errors that could occur while using
     *          this layer.
     */
    typedef enum {
        NotFound,
        NotAvailable,
        InvalidArguments
    } Error_t;

public:
    virtual ~DataLyr_Person() {}

    virtual QList<Person> getAllPersons() throw(Error_t) = 0;
    virtual Person getPerson( UniqueId personId ) throw(Error_t) = 0;
    virtual void createPerson( const Person& newPerson ) throw(Error_t) = 0;
    virtual void changePerson( const Person& changedPerson ) throw(Error_t) = 0;
    virtual void deletePerson( const UniqueId personId ) throw(Error_t) = 0;
};


} // namespace Data

} // namespace Dotoo


#endif // DATALYR_PERSON_H
