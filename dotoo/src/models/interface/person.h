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

    UniqueId getId() const;
    PersonName_t getName() const;
    QString getComment() const;

    void setId( const UniqueId id );
    void setName( const PersonName_t& name );
    void setComment( const QString& comment );

private:
    std::shared_ptr<PersonImpl> m_pImpl;
};

} // namespace Dotoo


#endif // PERSON_H
