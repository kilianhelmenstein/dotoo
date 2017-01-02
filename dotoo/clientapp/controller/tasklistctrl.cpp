#include "tasklistctrl.h"

#include <QPropertyAnimation>

#include "utilz/qanimationutilz.h"

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
    connect( view, &TaskListView::filterChanged, this, &TaskListCtrl::onFilterChanged );
}


/* Private slots: */

void TaskListCtrl::onClickedUpdate()
{
    m_model->getAllTasks();
}


void TaskListCtrl::onClickedAdd()
{
    TaskViewModel* model = m_model->createDummy();      // Create new dummy as data holder
    TaskEditView* editView = createEditView( TaskEditCtrl::Create,
                                             model );
    model->setParent( editView );

    connect( editView, &TaskEditView::destroyed,
             [this] () { m_view->setVisualFocus( true ); });
    //m_view->setVisualFocus( false );
    editView->show();
}


void TaskListCtrl::onClickedChange()
{
    onDoubleClickedTask( m_view->selectedTask() );
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
             [this] () { m_view->setVisualFocus( true ); });

    //m_view->setVisualFocus( false );
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


void TaskListCtrl::onFilterChanged()
{
    QPropertyFiltering::QPropertyFilter newFilter;
    QList<QVariant> matchValues;
    QPropertyFiltering::FilterSetting prototypeFilter;
    prototypeFilter.enabled = true;
    prototypeFilter.logic = QPropertyFiltering::Included;

    if ( m_view->filterEnabled() )
    {
        // Fill filtering object:
        matchValues.clear();
        matchValues.append( m_view->filterValueIsDone() );
        prototypeFilter.property = "isDone";
        prototypeFilter.mode = QPropertyFiltering::FullMatch;
        prototypeFilter.matchValues = matchValues;
        newFilter.installFilterSetting( prototypeFilter );
    }

    if ( !m_view->filterSearchString().isEmpty() )
    {
        matchValues.clear();
        matchValues.append( m_view->filterSearchString() );
        prototypeFilter.mode = QPropertyFiltering::PartialMatch;
        prototypeFilter.matchValues = matchValues;

        prototypeFilter.property = "title";
        newFilter.installFilterSetting( prototypeFilter );

        prototypeFilter.property = "comment";
        newFilter.installFilterSetting( prototypeFilter );
    }

    m_model->setPropertyFilter( newFilter );
}


TaskEditView* TaskListCtrl::createEditView( TaskEditCtrl::Mode modeSelection,
                                            TaskViewModel* usedModel ) const
{
    TaskEditView* editView = new TaskEditView( QPalette() );
    editView->setModel( usedModel );
    TaskEditCtrl* editCtrl = new TaskEditCtrl( modeSelection, editView, m_model, editView );

    QPropertyAnimation* fadeoutAnimation = QAnimationUtilz::CreateShrinkAnimation( editView, 1 );

    connect( editCtrl, &TaskEditCtrl::userFinished,
             [=]() { fadeoutAnimation->start(); } );
    connect( fadeoutAnimation, &QPropertyAnimation::finished,
             [=]() { editView->deleteLater(); fadeoutAnimation->deleteLater(); } );

    // Arrange within list view:
    editView->setParent( m_view );
    editView->setGeometry( m_view->width()/2 - editView->width()/2,
                           m_view->height()/2 - editView->height()/2,
                           editView->width(),
                           editView->height() );        // Center in tasklist view.

    return editView;
}


} // namespace GUI
} // nameespace Dotoo
