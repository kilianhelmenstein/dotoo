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
    void onClickedUpdate();
    void onClickedAdd();
    void onClickedChange();
    void onClickedDelete();
    void onDoubleClickedTask( TaskView* view );
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
