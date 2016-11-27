#ifndef TASK_H
#define TASK_H

/********************* Includes *********************/

#include <QtGlobal>

#include <memory>

#include "libsymbolsexport.h"
#include "decl/taskdecl.h"
#include "types/commontypes.h"
#include "types/tasktypes.h"



/******************** Namespaces ********************/

namespace Dotoo {


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
    Task( Task &other );
    ~Task();

    Task& operator=( const Task& other );

    /*!
     * \brief   Swaps the content of other with content of *this.
     *
     * \param   Task& other     The one of both swapped objects.
     */
    void swap( Task& other );

    /*!
     * \brief   Delivers the unique id for this task.
     *
     * \return  UniqueId      Unique id for this task.
     */
    UniqueId getId() const;

    /*!
     * \brief   Delivers whether task has been done already.
     *
     * \return  bool        true    -> Task is done.
     *                      false   -> Task is still open.
     */
    bool isDone() const;

    /*!
     * \brief   Delivers the person which is responsible for this task.
     *
     * \return  UniqueId    Unique id that refers to the responsible person.
     */
    UniqueId getResponsible() const;

    /*!
     * \brief   Delivers the creator of this task.
     *
     * \return  UniqueId    Unique id that refers to the creator of this task.
     */
    UniqueId getCreator() const;

    /*!
     * \brief   Delivers the date of task creation.
     *
     * \return  QDate       Creation date of this task.
     */
    QDate getCreationDate() const;

    /*!
     * \brief   Delivers the due date of this task.
     *
     * \return  QDate       Due date of this task.
     */
    QDate getDueDate() const;

    /*!
     * \brief   Delivers the priority of this task.
     *
     * \return  TaskPriority    Priority of this task.
     */
    TaskPriority getPriority() const;

    /*!
     * \brief   Delivers the project, the task is related to.
     *
     * \return  UniqueId   Unique id that refers to the related project.
     */
    UniqueId getRelatedProject() const;

    /*!
     * \brief   Returns a comment to this task as string.
     *
     * \return  QString     Some free-chosen comment.
     */
    QString getComment() const;

private:
    std::shared_ptr<TaskImpl> m_pImpl;
};

} // namespace Dotoo

#endif // TASK_H
