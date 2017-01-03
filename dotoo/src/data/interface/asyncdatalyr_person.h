#ifndef ASYNCDATALYR_PERSON_H
#define ASYNCDATALYR_PERSON_H


#include <QObject>

#include "project/libsymbolsexport.h"
#include "data/interface/datalyr_types.h"
#include "models/interface/types/commontypes.h"



namespace Dotoo {

class Person;


namespace Data {


/*!
 * \brief   The AsyncDataLyr_Person class is given to clients of AsyncDataLyr_Person
 *          to receive the responses of only their requests.
 */
class LIB_EXPORT AsyncDataLyr_PersonResponse : public QObject
{
    Q_OBJECT
signals:
    /*!
     * \brief   Emitted when response of getAllPersons request is received.
     *          Client is responsible for deleting 'allPersons' list.
     */
    void responseGetAllPersons( QList<Person>* allPersons, Error_t errorCode );

    /*!
     * \brief   Emitted when response of getPerson request is received.
     *          Client is responsible for deleting 'Person'.
     */
    void responseGetPerson( Person* person, Error_t errorCode );

    /*!
     * \brief   Emitted when response of createPerson request is received.
     */
    void responseCreatePerson( Error_t errorCode );

    /*!
     * \brief   Emitted when response of changePerson request is received.
     */
    void responseChangePerson( Error_t errorCode );

    /*!
     * \brief   Emitted when response of deletePerson request is received.
     */
    void responseDeletePerson( Error_t errorCode );
};



/*!
 * \brief   The AsyncDataLyr_Person class provides an interface for requesting
 *          Person data asynchronously. Objects are designed to work with only ONE client.
 */
class LIB_EXPORT AsyncDataLyr_Person : public QObject
{
    Q_OBJECT
public:
    AsyncDataLyr_Person( QObject* parent=nullptr ) : QObject( parent ) {}
    virtual ~AsyncDataLyr_Person() {}

    /*!
     * \brief   Tries to get all available Persons.
     *
     * \return  AsyncDataLyr_PersonResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_PersonResponse* getAllPersons() = 0;

    /*!
     * \brief   Tries to get the specified Person.
     *
     * \return  AsyncDataLyr_PersonResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_PersonResponse* getPerson( const UniqueId personId ) = 0;

    /*!
     * \brief   Tries to create a new Persons that equals to newPerson.
     *
     * \return  AsyncDataLyr_PersonResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_PersonResponse* createPerson( const Person& newPerson ) = 0;

    /*!
     * \brief   Tries to change the a Persons by using the attributes of
     *          changedPerson. The Person to change is referenced by changedPerson's id.
     *
     * \return  AsyncDataLyr_PersonResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_PersonResponse* changePerson( const Person& changedPerson ) = 0;

    /*!
     * \brief   Tries to delete the specified Person.
     *
     * \return  AsyncDataLyr_PersonResponse*  Might be used by clients to
     *                                      receive only their responses.
     */
    virtual AsyncDataLyr_PersonResponse* deletePerson( const UniqueId personId ) = 0;
};


} // namespace Data;
} // namespace Dotoo;


#endif // ASYNCDATALYR_PERSON_H
