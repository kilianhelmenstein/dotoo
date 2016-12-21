#include <utility>

#include "taskviewmodel.h"
#include "data/interface/asyncdatalyr_task.h"


namespace Dotoo {
namespace GUI {



TaskViewModel::TaskViewModel( Data::AsyncDataLyr_Task* datalayer,
                              QObject* parent )
    : QObject( parent ),
      m_datalayer( datalayer )
{
}



TaskViewModel::TaskViewModel( Data::AsyncDataLyr_Task* datalayer,
                              const Task& task, QObject* parent )
    : QObject( parent ),
      Task( task ),
      m_datalayer( datalayer )
{
}


TaskViewModel::TaskViewModel( const TaskViewModel& other )
    : QObject( other.parent() ),
      Task( other )
{
}


TaskViewModel::~TaskViewModel()
{
}


TaskViewModel& TaskViewModel::operator =( const Task& other )
{
    Task::operator =( other );
    emit changed();
    return *this;
}


TaskViewModel& TaskViewModel::operator =( const Task&& other )
{
    Task::operator =( other );
    emit changed();
    return *this;
}


void TaskViewModel::setDone( const bool isDone )
{
    Task::setDone( isDone );
    emit changed();
}

void TaskViewModel::setResponsible( const UniqueId responsible )
{
    Task::setResponsible( responsible );
    emit changed();
}

void TaskViewModel::setCreator( const UniqueId creator )
{
    Task::setCreator( creator );
    emit changed();
}

void TaskViewModel::setCreationDate( const QDate& creationDate )
{
    Task::setCreationDate( creationDate );
    emit changed();
}

void TaskViewModel::setDueDate( const QDate& dueDate )
{
    Task::setDueDate( dueDate );
    emit changed();
}

void TaskViewModel::setPriority( const TaskPriority priority )
{
    Task::setPriority( priority );
    emit changed();
}

void TaskViewModel::setRelatedProject( const UniqueId relatedProject )
{
    Task::setRelatedProject( relatedProject );
    emit changed();
}

void TaskViewModel::setComment( const QString& comment )
{
    Task::setComment( comment );
    emit changed();
}


/* Interface for controller: */

void TaskViewModel::get()
{
    using namespace Data;

    AsyncDataLyr_TaskResponse* rsp = m_datalayer->getTask(getId());
    connect( rsp, &AsyncDataLyr_TaskResponse::responseGetTask,
             this, &TaskViewModel::onResponseGetTask );
    connect( rsp, &AsyncDataLyr_TaskResponse::responseGetTask,
             rsp, &AsyncDataLyr_TaskResponse::deleteLater );
}


void TaskViewModel::change()
{
    using namespace Data;

    AsyncDataLyr_TaskResponse* rsp = m_datalayer->changeTask( *this );
    connect( rsp, &AsyncDataLyr_TaskResponse::responseChangeTask,
             this, &TaskViewModel::onResponseChangeTask );
    connect( rsp, &AsyncDataLyr_TaskResponse::responseChangeTask,
             rsp, &AsyncDataLyr_TaskResponse::deleteLater );
}


/* Response slots for using Data::AsyncDataLyr_Task: */

void TaskViewModel::onResponseGetTask( Task* task, Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {
        operator =(*task);
        emit changed();
    }

    delete task;
}


void TaskViewModel::onResponseChangeTask( Data::Error_t errorCode )
{
    if ( errorCode == Data::None )
    {

    }
}


} // namespace GUI
} // namespace Dotoo
