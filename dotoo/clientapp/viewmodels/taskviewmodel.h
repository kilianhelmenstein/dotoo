#ifndef TASKVIEWMODEL_H
#define TASKVIEWMODEL_H

#include <QObject>

#include "models/interface/task.h"
#include "data/interface/datalyr_fwddecl.h"
#include "data/interface/datalyr_types.h"

#include <QDate>
#include <QString>


/******************** Namespaces ********************/

namespace Dotoo {
namespace GUI {



/*********************** Class **********************/

/*!
 * \brief   The TaskViewModel class wrapps the 'Task' model class with
 *              - functionality needed by views (like changed-signals)
 *              - functionality needed by controllerse (update data, change data...)
 */
class TaskViewModel : public QObject, public Task
{
    Q_OBJECT

    Q_PROPERTY( UniqueId id READ getId WRITE setId NOTIFY changed )
    Q_PROPERTY( QString title READ getTitle WRITE setTitle NOTIFY changed )
    Q_PROPERTY( bool isDone READ isDone WRITE setDone NOTIFY changed )
    Q_PROPERTY( UniqueId responsible READ getResponsible WRITE setResponsible NOTIFY changed )
    Q_PROPERTY( UniqueId creator READ getCreator WRITE setCreator NOTIFY changed )
    Q_PROPERTY( QDate creationDate READ getCreationDate WRITE setCreationDate NOTIFY changed )
    Q_PROPERTY( QDate dueDate READ getDueDate WRITE setDueDate NOTIFY changed )
    Q_PROPERTY( TaskPriority priority READ getPriority WRITE setPriority NOTIFY changed )
    Q_PROPERTY( UniqueId relatedProject READ getRelatedProject WRITE setRelatedProject NOTIFY changed )
    Q_PROPERTY( QString comment READ getComment WRITE setComment NOTIFY changed )

public:
    TaskViewModel( Data::AsyncDataLyr_Task* datalayer,
                   QObject* parent=nullptr );
    TaskViewModel( Data::AsyncDataLyr_Task* datalayer,
                   const Task& task, QObject* parent=nullptr );
    TaskViewModel( const TaskViewModel& other );

    virtual ~TaskViewModel();

    virtual TaskViewModel& operator =( const Task& other );
    virtual TaskViewModel& operator =( const Task&& other );

    void setDone( const bool isDone );
    void setTitle( const QString& title );
    void setResponsible( const UniqueId responsible );
    void setCreator( const UniqueId creator );
    void setCreationDate( const QDate& creationDate );
    void setDueDate( const QDate& dueDate );
    void setPriority( const TaskPriority priority );
    void setRelatedProject( const UniqueId relatedProject );
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
    /* Response slots for using Data::AsyncDataLyr_Task: */
    void onResponseGetTask( Task* task, Data::Error_t errorCode );
    void onResponseChangeTask( Data::Error_t errorCode );

private:
    Data::AsyncDataLyr_Task* m_datalayer;
};


} // namespace GUI
} // namespace Dotoo

#endif // TASKVIEWMODEL_H
