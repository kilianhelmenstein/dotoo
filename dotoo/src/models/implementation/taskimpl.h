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
              const bool isDone,
              const UniqueId responsible,
              const UniqueId creator,
              const QDate& creationDate,
              const QDate& dueDate,
              const TaskPriority priority,
              const UniqueId relatedProject,
              const QString& comment );
    virtual ~TaskImpl();

    /* Interface implementation. For detailed interface description see "task.h".
     * (Using in-class-def for inline-reasons)
     */
    UniqueId getId() const { return m_id; }
    bool isDone() const { return m_isDone; }
    UniqueId getResponsible() const{ return m_responsible; }
    UniqueId getCreator() const{ return m_creator; }
    QDate getCreationDate() const{ return *m_creationDate; }
    QDate getDueDate() const{ return *m_dueDate; }
    TaskPriority getPriority() const{ return m_priority; }
    UniqueId getRelatedProject() const{ return m_relatedProject; }
    QString getComment() const{ return *m_comment; }


private:
    UniqueId m_id;
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
