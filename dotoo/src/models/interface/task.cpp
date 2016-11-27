#include "models/implementation/taskimpl.h"
#include "task.h"



using namespace std;
using namespace Dotoo;


QString toString( const QDate& date )
{
    return date.toString( "YYYY-MM-DD hh:mm:ss" );
}



QDate fromString( const QString& dateStr )
{
    return QDate::fromString( dateStr, "YYYY-MM-DD hh:mm:ss" );
}



Task::Task()
    : m_pImpl( new TaskImpl( 0,
                             false,
                             0,
                             0,
                             QDate::currentDate(),
                             QDate::currentDate(),
                             0,
                             0,
                             "" ) )
{
}


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


Task& Task::operator=( const Task& other )
{
    if ( this != &other )
    {
        m_pImpl.reset( new TaskImpl( *(other.m_pImpl) ) );
    }

    return *this;
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

