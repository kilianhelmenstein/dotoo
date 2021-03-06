#ifndef PERSONIMPL_H
#define PERSONIMPL_H

#include <memory>

#include "types/commontypes.h"
#include "types/persontypes.h"



namespace Dotoo {


class PersonImpl
{
public:
    PersonImpl( const UniqueId& id,
                const PersonName_t& name,
                const QString& comment );
    PersonImpl( const PersonImpl& other );
    virtual ~PersonImpl();

    PersonImpl& operator=( const PersonImpl& other );

    void swap( PersonImpl& other );

    UniqueId getId() const { return m_id; }
    PersonName_t getName() const { return *m_name; }
    QString getComment() const { return *m_comment; }

    void setId( const UniqueId id ) { m_id = id; }
    void setName( const PersonName_t& name ) { *m_name = name; }
    void setComment( const QString& comment ) { *m_comment = comment; }

private:
    UniqueId m_id;
    std::shared_ptr<PersonName_t> m_name;
    std::shared_ptr<QString> m_comment;
};

} // namespace Dotoo


#endif // PERSONIMPL_H
