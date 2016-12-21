#ifndef TASKLISTVIEWMODEL_H
#define TASKLISTVIEWMODEL_H

#include <QObject>
#include <QList>

#include "models/interface/task.h"
#include "data/interface/datalyr_fwddecl.h"
#include "data/interface/datalyr_types.h"



/******************** Namespaces ********************/

namespace Dotoo {
namespace GUI {


class TaskViewModel;



/*********************** Class **********************/

class TaskListViewModel : public QObject
{
    Q_OBJECT
public:
    TaskListViewModel( Data::AsyncDataLyr_Task* datalayer,
                       QObject* parent=nullptr );
    virtual ~TaskListViewModel();

    void setDatalayer( Data::AsyncDataLyr_Task* datalayer );

    /*!
     * \brief   Updates model list by using injected datalayer.
     */
    void getAllTasks();

    /*!
     * \brief   Creates the new task by using injected datalayer.
     *
     * \param newTask
     */
    void createTask( Task* newTask );

    /*!
     * \brief   Deletes a task by using injected datalayer.
     * \param taskId
     */
    void deleteTask( UniqueId taskId );

    Data::AsyncDataLyr_Task* dataLayer() const { return m_datalayer; }
    QList<TaskViewModel*> modelList() const { return m_modelList; }

signals:
    /*!
     * \brief   This signal is emitted when data changes, e.g. by calling
     *          getAllTasks(), createTask() or deleteTask().
     */
    void changed();


private slots:
    /* Response slots for using Data::AsyncDataLyr_Task: */
    void onResponseGetAllTasks( QList<Task>* allTasks, Data::Error_t errorCode );
    void onResponseCreateTask( Data::Error_t errorCode );
    void onResponseDeleteTask( Data::Error_t errorCode );

private:
    Data::AsyncDataLyr_Task* m_datalayer;       /*!< Dependency: Used for accessing real data. */
    QList<TaskViewModel*> m_modelList;          /*!< List with all task models. */
};


} // namespace GUI
} // namespace Dotoo

#endif // TASKLISTVIEWMODEL_H
