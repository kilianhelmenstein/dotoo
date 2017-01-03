#include "personeditctrl.h"

#include <QDate>

#include "personeditview.h"
#include "personlistviewmodel.h"


namespace Dotoo {
namespace GUI {



PersonEditCtrl::PersonEditCtrl( Mode mode,
                                PersonEditView* view,
                                PersonListViewModel* listModel,
                                QObject* parent )
    : QObject( parent ),
      m_mode( mode ),
      m_view( view ),
      m_listModel( listModel )
{
    connect( view, &PersonEditView::clickedAbort,
             this, &PersonEditCtrl::onClickedAbort );
    connect( view, &PersonEditView::clickedApply,
             this, &PersonEditCtrl::onClickedApply );
}


void PersonEditCtrl::onClickedAbort()
{
    // Do nothing.
    emit userFinished();
}


void PersonEditCtrl::onClickedApply()
{
    if ( WriteModel( *m_view, m_view->model() ) )
    {
        switch ( mode() )
        {
        case Change:
            m_view->model()->change();
            break;
        case Create:
            m_listModel->createPerson( m_view->model() );
        }
    }

    emit userFinished();
}


bool PersonEditCtrl::WriteModel( const PersonEditView& view,
                                 PersonViewModel* model )
{
    if ( model )
    {
        // Set model's attribute (set by user):
        model->setName( { view.forename(), view.name() } );
        model->setComment( view.comment() );
        return true;
    }

    return false;
}


} // namespace GUI
} // nameespace Dotoo
