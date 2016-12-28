#include "tasklistviewmodel.h"

#include "viewmodels/taskviewmodel.h"
#include "data/interface/asyncdatalyr_task.h"



/******************** Namespaces ********************/

namespace Dotoo {
namespace GUI {


TaskListViewModel::TaskListViewModel( Data::AsyncDataLyr_Task *datalayer,
                                      QObject* parent )
    : QObject(parent),
      m_datalayer(datalayer)
{

}


TaskListViewModel::~TaskListViewModel()
{
}


void TaskListViewModel::setDatalayer( Data::AsyncDataLyr_Task* datalayer )
{
    if ( datalayer )
    {
        m_datalayer = datalayer;
    }
}


void TaskListViewModel::getAllTasks()
{
    using namespace Data;

    AsyncDataLyr_TaskResponse* rsp = m_datalayer->getAllTasks();
    connect( rsp, &AsyncDataLyr_TaskResponse::responseGetAllTasks,
             this, &TaskListViewModel::onResponseGetAllTasks );
    connect( rsp, &AsyncDataLyr_TaskResponse::responseGetAllTasks,
             rsp, &AsyncDataLyr_TaskResponse::deleteLater );
}


void TaskListViewModel::createTask( Task* newTask )
{
    using namespace Data;

    AsyncDataLyr_TaskResponse* rsp = m_datalayer->createTask(*newTask);
    connect( rsp, &AsyncDataLyr_TaskResponse::responseCreateTask,
             this, &TaskListViewModel::onResponseCreateTask );
    connect( rsp, &AsyncDataLyr_TaskResponse::responseCreateTask,
             rsp, &AsyncDataLyr_TaskResponse::deleteLater );
}


void TaskListViewModel::deleteTask( UniqueId taskId )
{
    using namespace Data;

    AsyncDataLyr_TaskResponse* rsp = m_datalayer->deleteTask(taskId);
    connect( rsp, &AsyncDataLyr_TaskResponse::responseDeleteTask,
             this, &TaskListViewModel::onResponseDeleteTask );
    connect( rsp, &AsyncDataLyr_TaskResponse::responseDeleteTask,
             rsp, &AsyncDataLyr_TaskResponse::deleteLater );
}


TaskViewModel* TaskListViewModel::createDummy( QObject* parent ) const
{
    return new TaskViewModel( m_datalayer, parent );
}


/* Response slots: */

void TaskListViewModel::onResponseGetAllTasks( QList<Task>* allTasks, Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {
        QList<TaskViewModel*>::iterator currentOldTask = m_modelList.begin();
        bool oldListsEndReached = false;

        // Replace old viewmodels by updated ones
        QList<Task>::iterator currentUpdatedTask = allTasks->begin();
        for ( ; currentUpdatedTask != allTasks->end()
              ; ++currentUpdatedTask )
        {
            if ( currentOldTask != m_modelList.end() )
            {
                **currentOldTask = *currentUpdatedTask; // Replace old task by updated one.
                ++currentOldTask;                       // Select next old task.
            } else
            {
                oldListsEndReached = true;
                break;                                  // No more old entries to overwrite
            }
        }

        // I m_modelList was to short --> Create new instances for the additional tasks:
        for ( ; currentUpdatedTask != allTasks->end()
              ; ++currentUpdatedTask )
        {
            // If 'allTasks' is greater than m_modelList --> Create new viewmodel instance:
            m_modelList.append( new TaskViewModel(m_datalayer,
                                                  *currentUpdatedTask,
                                                  this) );
        }

        // If m_modelList is greater than 'allTasks' --> Remove remaining task viewmodels:
        if ( oldListsEndReached == false )
        {
            for ( QList<TaskViewModel*>::iterator toDelete = currentOldTask ; toDelete != m_modelList.end()
                  ; ++toDelete )
            {
                (*currentOldTask)->deleteLater();
            }
            m_modelList.erase( currentOldTask, m_modelList.end() );
        }
    }

    delete allTasks;
    emit changed();
}


void TaskListViewModel::onResponseCreateTask( Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {
        getAllTasks();
    }
}


void TaskListViewModel::onResponseDeleteTask( Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {
        getAllTasks();
    }
}


} // namespace GUI
} // namespace Dotoo
