#ifndef TASKVIEWMODEL_H
#define TASKVIEWMODEL_H

#include <QObject>

#include "models/interface/task.h"
#include "data/interface/datalyr_fwddecl.h"
#include "data/interface/datalyr_types.h"



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
