#include "person.h"
#include "models/implementation/personimpl.h"



using namespace Dotoo;



Person::Person()
    : m_pImpl( new PersonImpl( 0,
                               PersonName_t( "", "" ),
                               "" ) )
{
}


Person::Person( const UniqueId& id,
                const PersonName_t& name,
                const QString& comment )
    : m_pImpl( new PersonImpl( id,
                               name,
                               comment ) )
{
}


Person::Person( const Person& other )
    : m_pImpl( new PersonImpl( *(other.m_pImpl) ) )
{
}


Person::Person( const Person&& other )
    : m_pImpl( other.m_pImpl.get() )
{
}


Person::~Person()
{
}


Person& Person::operator =( const Person& other )
{
    if ( this != &other )
    {
        m_pImpl.reset( new PersonImpl( *(other.m_pImpl) ) );
    }

    return *this;
}


Person& Person::operator =( const Person&& other )
{
    if ( this != &other )
    {
        m_pImpl.reset( other.m_pImpl.get() );
    }

    return *this;
}


bool Person::operator ==( const Person& other )
{
    return (getId() == other.getId()
            && getName() == other.getName()
            && getComment() == other.getComment() );
}


bool Person::operator !=( const Person& other)
{
    return !(*this == other );
}


void Person::swap( Person& other )
{
    m_pImpl.swap( other.m_pImpl );
}


UniqueId Person::getId() const
{
    return m_pImpl->getId();
}

PersonName_t Person::getName() const
{
    return m_pImpl->getName();
}

QString Person::getComment() const
{
    return m_pImpl->getComment();
}

void Person::setId( const UniqueId id )
{
    m_pImpl->setId( id );
}

void Person::setName( const PersonName_t& name )
{
    m_pImpl->setName( name );
}

void Person::setComment( const QString& comment )
{
    m_pImpl->setComment( comment );
}
