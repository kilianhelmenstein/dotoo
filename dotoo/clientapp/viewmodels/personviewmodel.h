#ifndef PERSONVIEWMODEL_H
#define PERSONVIEWMODEL_H

#include <QObject>

#include "models/interface/person.h"
#include "data/interface/datalyr_fwddecl.h"
#include "data/interface/datalyr_types.h"

#include <QDate>
#include <QString>


/******************** Namespaces ********************/

namespace Dotoo {
namespace GUI {


/*********************** Class **********************/

/*!
 * \brief   The PersoniewModel class wrapps the 'Person' model class with
 *              - functionality needed by views (like changed-signals)
 *              - functionality needed by controllerse (update data, change data...)
 */
class PersonViewModel : public QObject, public Person
{
    Q_OBJECT

    Q_PROPERTY( UniqueId id READ getId WRITE setId NOTIFY changed )
    Q_PROPERTY( PersonName_t name READ getName WRITE setName NOTIFY changed )
    Q_PROPERTY( QString fullName READ getFullName NOTIFY changed )
    Q_PROPERTY( QString comment READ getComment WRITE setComment NOTIFY changed )

public:
    PersonViewModel( Data::AsyncDataLyr_Person* datalayer,
                     QObject* parent=nullptr );
    PersonViewModel( Data::AsyncDataLyr_Person* datalayer,
                     const Person& person, QObject* parent=nullptr );
    PersonViewModel( const PersonViewModel& other );

    virtual ~PersonViewModel();

    virtual PersonViewModel& operator =( const Person& other );
    virtual PersonViewModel& operator =( const Person&& other );

    void setId( const UniqueId id );
    void setName( const PersonName_t& name );
    void setComment( const QString& comment );

    /* Interface for controller: */

    /*!
     * \brief   Tries to get all attributes of entity and write it into this
     *          local model.
     */
    void get();

    /*!
     * \brief   Tries to write all attributes of this local model into entity.
     */
    void change();

signals:
    void changed();


private slots:
    /* Response slots for using Data::AsyncDataLyr_Person: */
    void onResponseGetPerson( Person* Person, Data::Error_t errorCode );
    void onResponseChangePerson( Data::Error_t errorCode );

private:
    Data::AsyncDataLyr_Person* m_datalayer;
};

} // namespace GUI
} // namespace Doto

#endif // PERSONVIEWMODEL_H
