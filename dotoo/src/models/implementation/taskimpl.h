#ifndef TASKIMPL_H
#define TASKIMPL_H

/********************* Includes *********************/

#include <memory>

#include <QDate>
#include <QString>

#include "types/commontypes.h"
#include "types/tasktypes.h"



/******************** Namespaces ********************/

namespace Dotoo {



/*********************** Class **********************/

/*!
 * \brief   The TaskImpl class implements the Task interface in a very basic way.
 */
class TaskImpl
{
public:
    TaskImpl( const UniqueId id,
              const QString& title,
              const bool isDone,
              const UniqueId responsible,
              const UniqueId creator,
              const QDate& creationDate,
              const QDate& dueDate,
              const TaskPriority priority,
              const UniqueId relatedProject,
              const QString& comment );
    TaskImpl( const TaskImpl& other );
    virtual ~TaskImpl();

    /* Interface implementation. For detailed interface description see "task.h".
     * (Using in-class-def for inline-reasons)
     */
    UniqueId getId() const { return m_id; }
    QString getTitle() const { return *m_title; }
    bool isDone() const { return m_isDone; }
    UniqueId getResponsible() const{ return m_responsible; }
    UniqueId getCreator() const{ return m_creator; }
    QDate getCreationDate() const{ return *m_creationDate; }
    QDate getDueDate() const{ return *m_dueDate; }
    TaskPriority getPriority() const{ return m_priority; }
    UniqueId getRelatedProject() const{ return m_relatedProject; }
    QString getComment() const{ return *m_comment; }

    void setId( const UniqueId id ) { m_id = id; }
    void setTitle( const QString& title ) { *m_title = title; }
    void setDone( const bool isDone ) { m_isDone = isDone; }
    void setResponsible( const UniqueId responsible ) { m_responsible = responsible; }
    void setCreator( const UniqueId creator ) { m_creator = creator; }
    void setCreationDate( const QDate& creationDate ) { *m_creationDate = creationDate; }
    void setDueDate( const QDate& dueDate ) { *m_dueDate = dueDate; }
    void setPriority( const TaskPriority priority ) { m_priority = priority; }
    void setRelatedProject( const UniqueId relatedProject ) { m_relatedProject = relatedProject; }
    void setComment( const QString& comment ) { *m_comment = comment; }

private:
    UniqueId m_id;
    std::shared_ptr<QString> m_title;
    bool m_isDone;
    UniqueId m_responsible;
    UniqueId m_creator;
    std::shared_ptr<QDate> m_creationDate;
    std::shared_ptr<QDate> m_dueDate;
    TaskPriority m_priority;
    UniqueId m_relatedProject;
    std::shared_ptr<QString> m_comment;
};


} // namespace Dotoo

#endif // TASKIMPL_H
