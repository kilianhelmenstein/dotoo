#include "personimpl.h"


using namespace Dotoo;



PersonImpl::PersonImpl( const UniqueId& id,
                        const PersonName_t& name,
                        const QString& comment )
    : m_id( id ),
      m_name( new PersonName_t(name) ),
      m_comment( new QString(comment) )
{

}


PersonImpl::PersonImpl( const PersonImpl &other )
    : m_id( other.m_id ),
      m_name( new PersonName_t(other.getName()) ),
      m_comment( new QString(other.getComment()) )
{
}


PersonImpl::~PersonImpl()
{

}




PersonImpl& PersonImpl::operator=( const PersonImpl& other )
{
    m_id = other.getId();
    *m_name = other.getName();
    *m_comment = other.getComment();

    return *this;
}



void PersonImpl::swap( PersonImpl& other )
{
    UniqueId tempId = m_id;
    m_id = other.getId();
    other.m_id = tempId;

    m_name.swap( other.m_name );
    m_comment.swap( other.m_comment );
}
