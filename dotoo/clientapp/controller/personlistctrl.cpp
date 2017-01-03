#include "personlistctrl.h"

#include <QPropertyAnimation>

#include "utilz/qanimationutilz.h"

#include "personlistviewmodel.h"
#include "personlistview.h"
#include "personview.h"

#include "personeditview.h"


namespace Dotoo {
namespace GUI {



PersonListCtrl::PersonListCtrl( PersonListViewModel* model,
                            PersonListView* view,
                            QObject* parent )
    : QObject( parent ),
      m_model( model ),
      m_view( view )
{
    // Connect to view:
    connect( view, &PersonListView::clickedUpdate, this, &PersonListCtrl::onClickedUpdate );
    connect( view, &PersonListView::clickedAdd, this, &PersonListCtrl::onClickedAdd );
    connect( view, &PersonListView::clickedChange, this, &PersonListCtrl::onClickedChange );
    connect( view, &PersonListView::clickedDelete, this, &PersonListCtrl::onClickedDelete );
    connect( view, &PersonListView::doubleClickedPerson, this, &PersonListCtrl::onDoubleClickedPerson );
    connect( view, &PersonListView::filterChanged, this, &PersonListCtrl::onFilterChanged );
}


/* Private slots: */

void PersonListCtrl::onClickedUpdate()
{
    m_model->getAllPersons();
}


void PersonListCtrl::onClickedAdd()
{
    PersonViewModel* model = m_model->createDummy();      // Create new dummy as data holder
    PersonEditView* editView = createEditView( PersonEditCtrl::Create,
                                             model );
    model->setParent( editView );

    connect( editView, &PersonEditView::destroyed,
             [this] () { m_view->setVisualFocus( true ); });
    //m_view->setVisualFocus( false );
    editView->show();
}


void PersonListCtrl::onClickedChange()
{
    onDoubleClickedPerson( m_view->selectedPerson() );
}


void PersonListCtrl::onClickedDelete()
{
    PersonView* selectedPerson = m_view->selectedPerson();
    if ( selectedPerson && selectedPerson->model() )
    {
        m_model->deletePerson( selectedPerson->model()->getId() );
    }
}


void PersonListCtrl::onDoubleClickedPerson( PersonView* view )
{
    PersonEditView* editView = createEditView( PersonEditCtrl::Change,
                                             view->model() );
    connect( editView, &PersonEditView::destroyed,
             [this] () { m_view->setVisualFocus( true ); });

    //m_view->setVisualFocus( false );
    editView->show();
}



void PersonListCtrl::onFilterChanged()
{
    QPropertyFiltering::QPropertyFilter newFilter;
    QList<QVariant> matchValues;
    QPropertyFiltering::FilterSetting prototypeFilter;
    prototypeFilter.enabled = true;
    prototypeFilter.logic = QPropertyFiltering::Included;

    if ( !m_view->filterSearchString().isEmpty() )
    {
        QList<QPropertyFiltering::FilterSetting> filterGroup;

        matchValues.clear();
        matchValues.append( m_view->filterSearchString() );
        prototypeFilter.mode = QPropertyFiltering::PartialMatch;
        prototypeFilter.matchValues = matchValues;
        prototypeFilter.matchIsMandatory = false;

        prototypeFilter.property = "fullName";
        filterGroup.append( prototypeFilter );

        prototypeFilter.property = "comment";
        filterGroup.append( prototypeFilter );

        newFilter.installFilterSettingGroup( filterGroup, QPropertyFiltering::OneMatching );
    }

    m_model->setPropertyFilter( newFilter );
}


PersonEditView* PersonListCtrl::createEditView( PersonEditCtrl::Mode modeSelection,
                                            PersonViewModel* usedModel ) const
{
    PersonEditView* editView = new PersonEditView( QPalette() );
    editView->setModel( usedModel );
    PersonEditCtrl* editCtrl = new PersonEditCtrl( modeSelection, editView, m_model, editView );

    QPropertyAnimation* fadeoutAnimation = QAnimationUtilz::CreateShrinkAnimation( editView, 1 );

    connect( editCtrl, &PersonEditCtrl::userFinished,
             [=]() { fadeoutAnimation->start(); } );
    connect( fadeoutAnimation, &QPropertyAnimation::finished,
             [=]() { editView->deleteLater(); fadeoutAnimation->deleteLater(); } );

    // Arrange within list view:
    editView->setParent( m_view );
    editView->setGeometry( m_view->width()/2 - editView->width()/2,
                           m_view->height()/2 - editView->height()/2,
                           editView->width(),
                           editView->height() );        // Center in Personlist view.

    return editView;
}


} // namespace GUI
} // nameespace Dotoo
