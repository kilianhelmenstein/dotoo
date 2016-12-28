#include "tasklistctrl.h"

#include "tasklistviewmodel.h"
#include "tasklistview.h"
#include "taskview.h"

#include "taskeditview.h"
#include "taskeditctrl.h"


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
    connect( view, &TaskListView::doubleClickedTask, this, &TaskListCtrl::onDoubleClickedTask );
    connect( view, &TaskListView::isDoneToggled, this, &TaskListCtrl::onIsDoneToggled );
}


/* Private slots: */

void TaskListCtrl::onClickedUpdate()
{
    m_model->getAllTasks();
}


void TaskListCtrl::onClickedAdd()
{
    TaskViewModel* model = m_model->createDummy();
    TaskEditView* editView = createEditView( TaskEditCtrl::Create,
                                                   model );
    model->setParent( editView );   // Dummy model needs a parent!

    editView->show();
}


void TaskListCtrl::onClickedChange()
{
    TaskEditView* editView = createEditView( TaskEditCtrl::Change,
                                                   m_view->selectedTask()->model() );

    editView->show();
}


void TaskListCtrl::onClickedDelete()
{
    TaskView* selectedTask = m_view->selectedTask();
    if ( selectedTask && selectedTask->model() )
    {
        m_model->deleteTask( selectedTask->model()->getId() );
    }
}


void TaskListCtrl::onDoubleClickedTask( TaskView* view )
{
    TaskEditView* editView = createEditView( TaskEditCtrl::Change,
                                                   view->model() );

    connect( editView, &TaskEditView::destroyed,
             [this] () { m_view->setBlurring( false ); });

    m_view->setBlurring( true );
    editView->show();
}


void TaskListCtrl::onIsDoneToggled( TaskView* view, bool isDone )
{
    TaskViewModel* model = view->model();
    if ( model )
    {
        model->setDone( isDone );           // Update local model with aid of view.
        model->change();                    // Update remote model.
    }
}


TaskEditView* TaskListCtrl::createEditView( TaskEditCtrl::Mode modeSelection,
                                                  TaskViewModel* usedModel ) const
{
    TaskEditView* editView = new TaskEditView( QPalette() );
    editView->setModel( usedModel );
    TaskEditCtrl* editCtrl = new TaskEditCtrl( modeSelection, editView, m_model, editView );

    connect( editCtrl, &TaskEditCtrl::userFinished,
             [=]() { editView->deleteLater(); } );

    return editView;
}


} // namespace GUI
} // nameespace Dotoo
