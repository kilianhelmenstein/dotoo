#ifndef TASKLISTCTRL_H
#define TASKLISTCTRL_H

#include <QObject>

#include "taskeditctrl.h"


namespace Dotoo {
namespace GUI {

class TaskView;
class TaskListView;
class TaskListViewModel;



/*!
 * \brief   The TaskListCtrl class is the controller of the 'TaskListView'.
 */
class TaskListCtrl : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief   Constructs a valid and working TaskListCtrl instance.
     *          Takes 'view' as the view, that is controlled by instantiated controller.
     *
     * \param   TaskListView* view      View for this controller.
     *
     * \param   QObject* parent         Parent of this object.
     */
    TaskListCtrl( TaskListViewModel* model,
                  TaskListView* view,
                  QObject* parent=nullptr );

signals:

public slots:

private slots:
    /*!
     * \brief   Forces reload of server data.
     */
    void onClickedUpdate();

    /*!
     * \brief   Creates a new view for creating a new task.
     */
    void onClickedAdd();

    /*!
     * \brief   Creates a new view for editing the clicked task.
     */
    void onClickedChange();

    /*!
     * \brief   Deletes the current selected task.
     */
    void onClickedDelete();

    /*!
     * \brief   Creates a new view for editing the clicked task.
     */
    void onDoubleClickedTask( TaskView* view );

    /*!
     * \brief   Changes the isDone flag of 'view's model to 'isDone' and updates the
     *          task's server entity.
     *
     * \param   TaskView* view      The view of the changed task.
     *
     * \param   bool isDone         The new 'isDone' state.
     */
    void onIsDoneToggled( TaskView* view, bool isDone );

private:
    /*!
     * \brief   Creates edit view for a task, a dummy model (that is used as data holder)
     *          and the right controller for the edit view.
     *
     * \param   TaskEditCtrl::Mode modeSelection    Mode selection for behavior of controller: Create a new task or change a existing one.
     *
     * \return
     */
    TaskEditView* createEditView( TaskEditCtrl::Mode modeSelection,
                                        TaskViewModel* usedModel ) const;

private:
    TaskListViewModel* m_model;     /*!< Stored reference to my model. */
    TaskListView* m_view;           /*!< Stored reference to my view. */
};


} // namespace GUI
} // namespace Dotoo

#endif // TASKLISTCTRL_H
