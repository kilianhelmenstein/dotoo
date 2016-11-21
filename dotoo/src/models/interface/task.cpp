#include "models/implementation/taskimpl.h"
#include "task.h"



using namespace std;
using namespace Dotoo;



Task::Task( const UniqueId id,
            const bool isDone,
            const UniqueId responsible,
            const UniqueId creator,
            const QDate& creationDate,
            const QDate& dueDate,
            const TaskPriority priority,
            const UniqueId relatedProject,
            const QString& comment )
    : m_pImpl( new TaskImpl( id,
                             isDone,
                             responsible,
                             creator,
                             creationDate,
                             dueDate,
                             priority,
                             relatedProject,
                             comment ) )
{
}


Task::Task( Task& other )
    : m_pImpl( new TaskImpl( *(other.m_pImpl) ) )
{
}


Task::~Task()
{
}


void Task::operator=( const Task& other )
{
    TaskImpl* temp = m_pImpl.get();
    m_pImpl.reset( new TaskImpl( *(other.m_pImpl) ) );
    delete temp;    /* Delete obsolete object when m_pImpl was reset. That will prevent a invalid pointer if an exception occurs. */
}


void Task::swap( Task& other )
{
    m_pImpl.swap( other.m_pImpl );
}


UniqueId Task::getId() const
{
    return m_pImpl->getId();
}

bool Task::isDone() const
{
    return m_pImpl->isDone();
}

UniqueId Task::getResponsible() const
{
    return m_pImpl->getResponsible();
}

UniqueId Task::getCreator() const
{
    return m_pImpl->getCreator();
}

QDate Task::getCreationDate() const
{
    return m_pImpl->getCreationDate();
}

QDate Task::getDueDate() const
{
    return m_pImpl->getDueDate();
}

TaskPriority Task::getPriority() const
{
    return m_pImpl->getPriority();
}

UniqueId Task::getRelatedProject() const
{
    return m_pImpl->getRelatedProject();
}

QString Task::getComment() const
{
    return m_pImpl->getComment();
}

