#include "personviewmodel.h"

#include <utility>

#include "data/interface/asyncdatalyr_person.h"


/******************** Namespaces ********************/

namespace Dotoo {
namespace GUI {


PersonViewModel::PersonViewModel( Data::AsyncDataLyr_Person* datalayer,
                                  QObject* parent )
    : QObject( parent ),
      m_datalayer( datalayer )
{
}



PersonViewModel::PersonViewModel( Data::AsyncDataLyr_Person* datalayer,
                                  const Person& person,
                                  QObject* parent )
    : QObject( parent ),
      Person( person ),
      m_datalayer( datalayer )
{
}


PersonViewModel::PersonViewModel( const PersonViewModel& other )
    : QObject( other.parent() ),
      Person( other )
{
}


PersonViewModel::~PersonViewModel()
{
}


PersonViewModel& PersonViewModel::operator =( const Person& other )
{
    Person::operator =( other );
    emit changed();
    return *this;
}


PersonViewModel& PersonViewModel::operator =( const Person&& other )
{
    Person::operator =( other );
    emit changed();
    return *this;
}


void PersonViewModel::setId( const UniqueId id )
{
    Person::setId( id );
    emit changed();
}

void PersonViewModel::setName( const PersonName_t& name )
{
    Person::setName( name );
    emit changed();
}

void PersonViewModel::setComment( const QString& comment )
{
    Person::setComment( comment );
    emit changed();
}


/* Interface for controller: */

void PersonViewModel::get()
{
    using namespace Data;

    AsyncDataLyr_PersonResponse* rsp = m_datalayer->getPerson(getId());
    connect( rsp, &AsyncDataLyr_PersonResponse::responseGetPerson,
             this, &PersonViewModel::onResponseGetPerson );
    connect( rsp, &AsyncDataLyr_PersonResponse::responseGetPerson,
             rsp, &AsyncDataLyr_PersonResponse::deleteLater );
}


void PersonViewModel::change()
{
    using namespace Data;

    AsyncDataLyr_PersonResponse* rsp = m_datalayer->changePerson( *this );
    connect( rsp, &AsyncDataLyr_PersonResponse::responseChangePerson,
             this, &PersonViewModel::onResponseChangePerson );
    connect( rsp, &AsyncDataLyr_PersonResponse::responseChangePerson,
             rsp, &AsyncDataLyr_PersonResponse::deleteLater );
}


/* Response slots for using Data::AsyncDataLyr_Person: */

void PersonViewModel::onResponseGetPerson( Person* Person, Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {
        operator =(*Person);
        emit changed();
    }

    delete Person;
}


void PersonViewModel::onResponseChangePerson( Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {

    }
}


} // namespace GUI
} // namespace Doto
