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
                             "",
                             false,
                             0,
                             0,
                             QDate::currentDate(),
                             QDate::currentDate(),
                             VeryImportant,
                             0,
                             "" ) )
{
}


Task::Task( const UniqueId id,
            const QString& title,
            const bool isDone,
            const UniqueId responsible,
            const UniqueId creator,
            const QDate& creationDate,
            const QDate& dueDate,
            const TaskPriority priority,
            const UniqueId relatedProject,
            const QString& comment )
    : m_pImpl( new TaskImpl( id,
                             title,
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


Task::Task( const Task& other )
    : m_pImpl( new TaskImpl( *(other.m_pImpl) ) )
{
}


Task::Task( const Task&& other )
    : m_pImpl( other.m_pImpl.get() )
{
}


Task::~Task()
{
}


Task& Task::operator =( const Task& other )
{
    if ( this != &other )
    {
        m_pImpl.reset( new TaskImpl( *(other.m_pImpl) ) );
    }

    return *this;
}


Task& Task::operator =( const Task&& other )
{
    if ( this != &other )
    {
        m_pImpl.reset( other.m_pImpl.get() );
    }

    return *this;
}


bool Task::operator ==( const Task& other )
{
    return (getId() == other.getId()
            && getTitle() == other.getTitle()
            && isDone() == other.isDone()
            && getResponsible() == other.getResponsible()
            && getCreator() == other.getCreator()
            && getCreationDate() == other.getCreationDate()
            && getDueDate() == other.getDueDate()
            && getPriority() == other.getPriority()
            && getRelatedProject() == other.getRelatedProject()
            && getComment() == other.getComment());
}


bool Task::operator !=( const Task& other )
{
    return !(*this == other);
}


void Task::swap( Task& other )
{
    m_pImpl.swap( other.m_pImpl );
}

UniqueId Task::getId() const
{
    return m_pImpl->getId();
}

QString Task::getTitle() const
{
    return m_pImpl->getTitle();
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

void Task::setId( const UniqueId id )
{
    m_pImpl->setId( id );
}

void Task::setTitle( const QString& title )
{
    m_pImpl->setTitle( title );
}

void Task::setDone( const bool isDone )
{
    m_pImpl->setDone( isDone );
}

void Task::setResponsible( const UniqueId responsible )
{
    m_pImpl->setResponsible( responsible );
}

void Task::setCreator( const UniqueId creator )
{
    m_pImpl->setCreator( creator );
}

void Task::setCreationDate( const QDate& creationDate )
{
    m_pImpl->setCreationDate( creationDate );
}

void Task::setDueDate( const QDate& dueDate )
{
    m_pImpl->setDueDate( dueDate );
}

void Task::setPriority( const TaskPriority priority )
{
    m_pImpl->setPriority( priority );
}

void Task::setRelatedProject( const UniqueId relatedProject )
{
    m_pImpl->setRelatedProject( relatedProject );
}

void Task::setComment( const QString& comment )
{
    m_pImpl->setComment( comment );
}

