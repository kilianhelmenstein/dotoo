#include "taskeditctrl.h"

#include <QDate>

#include "taskeditview.h"
#include "tasklistviewmodel.h"


namespace Dotoo {
namespace GUI {



TaskEditCtrl::TaskEditCtrl( Mode mode,
                            TaskEditView* view,
                            TaskListViewModel* listModel,
                            QObject* parent )
    : QObject( parent ),
      m_mode( mode ),
      m_view( view ),
      m_listModel( listModel )
{
    connect( view, &TaskEditView::clickedAbort,
             this, &TaskEditCtrl::onClickedAbort );
    connect( view, &TaskEditView::clickedApply,
             this, &TaskEditCtrl::onClickedApply );
}


void TaskEditCtrl::onClickedAbort()
{
    // Do nothing.
    emit userFinished();
}


void TaskEditCtrl::onClickedApply()
{
    if ( WriteModel( *m_view, m_view->model() ) )
    {
        switch ( mode() )
        {
        case Change:
            m_view->model()->change();
            break;
        case Create:
            m_listModel->createTask( m_view->model() );
        }
    }

    emit userFinished();
}


bool TaskEditCtrl::WriteModel( const TaskEditView& view,
                               TaskViewModel* model )
{
    if ( model )
    {
        // Set model's attribute (set by user):
        model->setTitle( view.title() );
        model->setComment( view.comment() );
        model->setDueDate( view.dueDate() );
        model->setCreator( view.creator() );
        model->setResponsible( view.responsible() );
        return true;
    }

    return false;
}


} // namespace GUI
} // nameespace Dotoo
