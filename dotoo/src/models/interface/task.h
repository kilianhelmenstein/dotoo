#ifndef TASK_H
#define TASK_H

/********************* Includes *********************/

#include <memory>

#include "project/libsymbolsexport.h"
#include "decl/taskdecl.h"
#include "types/commontypes.h"
#include "types/tasktypes.h"



/******************** Namespaces ********************/

namespace Dotoo {

class TaskImpl;



QString toString( const QDate& date );

QDate fromString( const QString& dateStr );


/*********************** Class **********************/

/*!
 * \brief   The Task class is the common interface for accessing Task instances.
 */
class LIB_EXPORT Task
{
public:
    Task();
    Task( const UniqueId id,
          const bool isDone,
          const UniqueId responsible,
          const UniqueId creator,
          const QDate& creationDate,
          const QDate& dueDate,
          const TaskPriority priority,
          const UniqueId relatedProject,
          const QString& comment );
    Task( const Task& other );
    Task( const Task&& other );
    ~Task();

    Task& operator =( const Task& other );
    Task& operator =( const Task&& other );

    bool operator ==( const Task& other );
    bool operator !=( const Task& other );

    /*!
     * \brief   Swaps the content of other with content of *this.
     *
     * \param   Task& other     The one of both swapped objects.
     */
    void swap( Task& other );

    UniqueId getId() const;
    bool isDone() const;
    UniqueId getResponsible() const;
    UniqueId getCreator() const;
    QDate getCreationDate() const;
    QDate getDueDate() const;
    TaskPriority getPriority() const;
    UniqueId getRelatedProject() const;
    QString getComment() const;

    virtual void setId( const UniqueId id );
    virtual void setDone( const bool isDone );
    virtual void setResponsible( const UniqueId responsible );
    virtual void setCreator( const UniqueId creator );
    virtual void setCreationDate( const QDate& creationDate );
    virtual void setDueDate( const QDate& dueDate );
    virtual void setPriority( const TaskPriority priority );
    virtual void setRelatedProject( const UniqueId relatedProject );
    virtual void setComment( const QString& comment );

private:
    std::shared_ptr<TaskImpl> m_pImpl;
};

} // namespace Dotoo

#endif // TASK_H
