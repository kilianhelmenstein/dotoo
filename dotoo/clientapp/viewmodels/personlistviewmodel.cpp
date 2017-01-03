#include "personlistviewmodel.h"

#include "viewmodels/personviewmodel.h"
#include "data/interface/asyncdatalyr_person.h"


/******************** Namespaces ********************/

namespace Dotoo {
namespace GUI {


PersonListViewModel::PersonListViewModel( Data::AsyncDataLyr_Person *datalayer,
                                          QObject* parent )
    : QObject(parent),
      m_datalayer(datalayer)
{
}


PersonListViewModel::~PersonListViewModel()
{
}


void PersonListViewModel::setDatalayer( Data::AsyncDataLyr_Person* datalayer )
{
    if ( datalayer )
    {
        m_datalayer = datalayer;
    }
}


void PersonListViewModel::getAllPersons()
{
    using namespace Data;

    AsyncDataLyr_PersonResponse* rsp = m_datalayer->getAllPersons();
    connect( rsp, &AsyncDataLyr_PersonResponse::responseGetAllPersons,
             this, &PersonListViewModel::onResponseGetAllPersons );
    connect( rsp, &AsyncDataLyr_PersonResponse::responseGetAllPersons,
             rsp, &AsyncDataLyr_PersonResponse::deleteLater );
}


void PersonListViewModel::createPerson( Person* newPerson )
{
    using namespace Data;

    AsyncDataLyr_PersonResponse* rsp = m_datalayer->createPerson(*newPerson);
    connect( rsp, &AsyncDataLyr_PersonResponse::responseCreatePerson,
             this, &PersonListViewModel::onResponseCreatePerson );
    connect( rsp, &AsyncDataLyr_PersonResponse::responseCreatePerson,
             rsp, &AsyncDataLyr_PersonResponse::deleteLater );
}


void PersonListViewModel::deletePerson( UniqueId personId )
{
    using namespace Data;

    AsyncDataLyr_PersonResponse* rsp = m_datalayer->deletePerson(personId);
    connect( rsp, &AsyncDataLyr_PersonResponse::responseDeletePerson,
             this, &PersonListViewModel::onResponseDeletePerson );
    connect( rsp, &AsyncDataLyr_PersonResponse::responseDeletePerson,
             rsp, &AsyncDataLyr_PersonResponse::deleteLater );
}


PersonViewModel* PersonListViewModel::createDummy( QObject* parent ) const
{
    return new PersonViewModel( m_datalayer, parent );
}


/* Response slots: */

void PersonListViewModel::onResponseGetAllPersons( QList<Person>* allPerson,
                                                   Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {
        QList<PersonViewModel*>::iterator currentOldPerson = m_modelList.begin();
        bool oldListsEndReached = false;

        // Replace old viewmodels by updated ones
        QList<Person>::iterator currentUpdatedPerson = allPerson->begin();
        for ( ; currentUpdatedPerson != allPerson->end()
              ; ++currentUpdatedPerson )
        {
            if ( currentOldPerson != m_modelList.end() )
            {
                **currentOldPerson = *currentUpdatedPerson; // Replace old Person by updated one.
                ++currentOldPerson;                       // Select next old Person.
            } else
            {
                oldListsEndReached = true;
                break;                                  // No more old entries to overwrite
            }
        }

        // I m_modelList was to short --> Create new instances for the additional Person:
        for ( ; currentUpdatedPerson != allPerson->end()
              ; ++currentUpdatedPerson )
        {
            // If 'allPerson' is greater than m_modelList --> Create new viewmodel instance:
            m_modelList.append( new PersonViewModel(m_datalayer,
                                                    *currentUpdatedPerson,
                                                    this) );
        }

        // If m_modelList is greater than 'allPerson' --> Remove remaining Person viewmodels:
        if ( oldListsEndReached == false )
        {
            for ( QList<PersonViewModel*>::iterator toDelete = currentOldPerson ; toDelete != m_modelList.end()
                  ; ++toDelete )
            {
                (*currentOldPerson)->deleteLater();
            }
            m_modelList.erase( currentOldPerson, m_modelList.end() );
        }
    }

    delete allPerson;

    updateFilteredModelList();
    emit changed();
}


void PersonListViewModel::onResponseCreatePerson( Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {
        getAllPersons();
    }
}


void PersonListViewModel::onResponseDeletePerson( Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {
        getAllPersons();
    }
}


void PersonListViewModel::updateFilteredModelList()
{
    m_filteredModelList.clear();

    foreach ( PersonViewModel* Person, m_modelList )
    {
        if ( m_filter.applyFilter( *Person ) )
        {
            m_filteredModelList.append( Person );
        }
    }
}


} // namespace GUI
} // namespace Dotoo
