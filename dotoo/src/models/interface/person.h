#ifndef PERSON_H
#define PERSON_H


/********************* Includes *********************/

#include <memory>

#include "project/libsymbolsexport.h"
#include "decl/persondecl.h"
#include "types/commontypes.h"
#include "types/persontypes.h"



/******************** Namespaces ********************/

namespace Dotoo {


class PersonImpl;



/*********************** Class **********************/

/*!
 * \brief   The Person class is the common interface for accessing Person instances.
 */
class LIB_EXPORT Person
{
public:
    Person();
    /*!
     * \brief Person
     *
     * \param id            Use id = 0 as invalid/unknown id (e.g. for creating a new pereson)
     *
     * \param name
     *
     * \param comment
     */
    Person( const UniqueId& id,
            const PersonName_t& name,
            const QString& comment );

    Person( const Person& other );
    Person( const Person&& other );

    virtual ~Person();

    Person& operator =( const Person& other );
    Person& operator =( const Person&& other );

    bool operator ==( const Person& other );
    bool operator !=( const Person& other);

    void swap( Person& other );

    /*!
     * \brief   Delivers the unique id for this person.
     *
     * \return  UniqueId            Unique id for this person.
     */
    UniqueId getId() const;

    /*!
     * \brief   Delivers the name of the person.
     *
     * \return  PersonName_t        Name of the person. See type documentation for further information.
     */
    PersonName_t getName() const;

    /*!
     * \brief   Returns a comment to this task as string.
     *
     * \return  QString     Some free-chosen comment.
     */
    QString getComment() const;

private:
    std::shared_ptr<PersonImpl> m_pImpl;
};

} // namespace Dotoo


#endif // PERSON_H
