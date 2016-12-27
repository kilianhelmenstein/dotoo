#include "tasklistctrl.h"

#include "tasklistviewmodel.h"
#include "tasklistview.h"
#include "taskview.h"


namespace Dotoo {
namespace GUI {



TaskListCtrl::TaskListCtrl( TaskListViewModel* model,
                            TaskListView* view,
                            QObject* parent )
    : QObject( parent ),
      m_model( model ),
      m_view( view )
{
    // Connect to view:
    connect( view, &TaskListView::clickedUpdate, this, &TaskListCtrl::onClickedUpdate );
    connect( view, &TaskListView::clickedAdd, this, &TaskListCtrl::onClickedAdd );
    connect( view, &TaskListView::clickedChange, this, &TaskListCtrl::onClickedChange );
    connect( view, &TaskListView::clickedDelete, this, &TaskListCtrl::onClickedDelete );
}


/* Private slots: */

void TaskListCtrl::onClickedUpdate()
{
    m_model->getAllTasks();
}


void TaskListCtrl::onClickedAdd()
{
    // TODO: Open 'Create-Task'-form
}


void TaskListCtrl::onClickedChange()
{
    // TODO: Open 'Change-Task'-form
}


void TaskListCtrl::onClickedDelete()
{
    TaskView* selectedTask = m_view->getSelectedTask();
    if ( selectedTask && selectedTask->model() )
    {
        m_model->deleteTask( selectedTask->model()->getId() );
    }
}


} // namespace GUI
} // nameespace Dotoo
