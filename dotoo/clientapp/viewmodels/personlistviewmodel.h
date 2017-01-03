#ifndef PERSONLISTVIEWMODEL_H
#define PERSONLISTVIEWMODEL_H


#include <QObject>
#include <QList>

#include "models/interface/person.h"
#include "data/interface/datalyr_fwddecl.h"
#include "data/interface/datalyr_types.h"
#include "ext/propfilter/qpropertyfiltering.h"


/******************** Namespaces ********************/

namespace Dotoo {
namespace GUI {


class PersonViewModel;



/*********************** Class **********************/

class PersonListViewModel : public QObject
{
    Q_OBJECT
public:
    PersonListViewModel( Data::AsyncDataLyr_Person* datalayer,
                         QObject* parent=nullptr );
    virtual ~PersonListViewModel();

    void setDatalayer( Data::AsyncDataLyr_Person* datalayer );

    /*!
     * \brief   Updates model list by using injected datalayer.
     */
    void getAllPersons();

    /*!
     * \brief   Creates the new person by using injected datalayer.
     *
     * \param   newPerson
     */
    void createPerson( Person* newPerson );

    /*!
     * \brief   Deletes a person by using injected datalayer.
     *
     * \param   PersonId
     */
    void deletePerson( UniqueId personId );

    Data::AsyncDataLyr_Person* dataLayer() const { return m_datalayer; }
    QList<PersonViewModel*> modelList() const { return m_modelList; }
    QList<PersonViewModel*> modelListFiltered() const { return m_filteredModelList; }

    /*!
     * \brief   Creates a dummy person viewmodel. Caller takes parentship.
     *
     * \return  New, unparented instance of PersonViewModel class with same datalayer of this
     *          object.
     */
    PersonViewModel* createDummy( QObject* parent=nullptr ) const;

    /*!
     * \brief   Sets the used object for filtering the Person list.
     *
     * \param   const QPropertyFiltering::QPropertyFilter& filter       Used filter object.
     */
    void setPropertyFilter( const QPropertyFiltering::QPropertyFilter& filter )
    {
        m_filter = filter;
        updateFilteredModelList();
        emit changed();
    }

signals:
    /*!
     * \brief   This signal is emitted when data changes, e.g. by calling
     *          getAllPersons(), createPerson() or deletePerson().
     */
    void changed();


private slots:
    /* Response slots for using Data::AsyncDataLyr_Person: */
    void onResponseGetAllPersons( QList<Person>* allPersons, Data::Error_t errorCode );
    void onResponseCreatePerson( Data::Error_t errorCode );
    void onResponseDeletePerson( Data::Error_t errorCode );

private:
    void updateFilteredModelList();

private:
    Data::AsyncDataLyr_Person* m_datalayer;           /*!< Dependency: Used for accessing real data. */
    QList<PersonViewModel*> m_modelList;              /*!< List with all Person models. */

    QPropertyFiltering::QPropertyFilter m_filter;   /*!< Used to filter Person list. */
    QList<PersonViewModel*> m_filteredModelList;      /*!< Result of applying filter settings on 'm_modelList' */
};


} // namespace GUI
} // namespace Dotoo


#endif // PERSONLISTVIEWMODEL_H
