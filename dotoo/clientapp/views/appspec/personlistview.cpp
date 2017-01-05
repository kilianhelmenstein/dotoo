#include "personlistview.h"

#include <QEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QRadialGradient>
#include <QSizePolicy>
#include <QLabel>
#include <QPropertyAnimation>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>

#include "viewmodels/personlistviewmodel.h"
#include "personview.h"
#include "utilz/textviewutilz.h"


namespace Dotoo {
namespace GUI {



PersonListView::PersonListView( const QPalette& appPalette,
                                QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr ),
      m_defaultPalette( appPalette ),
      m_looseFocusEffect( nullptr ),
      m_headline( nullptr ),
      m_listLayout( nullptr ),
      m_lblSearchString( nullptr ),
      m_leFilterSearchString( nullptr ),
      m_toolUpdate( nullptr ),
      m_toolAdd( nullptr ),
      m_toolChange( nullptr ),
      m_toolDelete( nullptr ),
      m_selectedPerson( nullptr )
{
    /****************************************************************/
    /*********             Initial Presenation:               *******/
    /****************************************************************/
    setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    setAutoFillBackground( true );

    /****************************************************************/
    /*********                Widget's Style:                 *******/
    /****************************************************************/
    setPalette( m_defaultPalette );
    setBackgroundRole( QPalette::Background );



    /****************************************************************/
    /*********             Widget's sub-widgets:              *******/
    /****************************************************************/

    /*** Headline: ***/
    QFont headlineFont;
    headlineFont.setPointSize( 30 );
    headlineFont.setStyleHint( QFont::SansSerif );
    headlineFont.setWeight( 30 );
    m_headline = new QLabel();
    m_headline->setFont( headlineFont );

    /*** Filter selection: ***/
    m_lblSearchString = new QLabel( tr("Search:") );
    m_leFilterSearchString = new QLineEdit();
    connect( m_leFilterSearchString, &QLineEdit::textChanged,
             this, &PersonListView::filterChanged );

    /*** Person list: ***/
    // Use 'mainWidget' for usage of scroll area (takes only a widget, no layouts):
    QWidget* mainWidget = new QWidget( this );
    mainWidget->setMinimumSize( 600, 500 );             // TODO: Use PersonView's min. size
    mainWidget->setPalette( m_defaultPalette );
    mainWidget->installEventFilter( this );             // mainWidget does not have functionality. Forward events to true widet.

    // Scroll area for list:
    QScrollArea* scrollArea = new QScrollArea( /*this*/ );
    scrollArea->setPalette( m_defaultPalette );
    scrollArea->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    scrollArea->setMinimumSize( minimumSize() );
    scrollArea->setWidgetResizable( true );
    scrollArea->setBackgroundRole( QPalette::Background );    // TODO: Maybe add a gradient would look nice.
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setFrameShape( QFrame::NoFrame );
    scrollArea->installEventFilter( this );
    scrollArea->setWidget( mainWidget );

    /*** Tool bar: ***/
    m_toolUpdate = new CustomGUI::CustomIconButton( ":svg/update_icon_normal",
                                                    ":svg/update_icon_mover",
                                                    ":svg/update_icon_selected",
                                                    false );
    m_toolUpdate->setFixedSize( 70,70 );
    connect( m_toolUpdate, &CustomGUI::CustomIconButton::clicked,
             this, &PersonListView::clickedUpdate );      // Forward buttons signal.
    m_toolAdd = new CustomGUI::CustomIconButton( ":svg/add_icon_normal",
                                                 ":svg/add_icon_mover",
                                                 ":svg/add_icon_selected",
                                                 false );
    m_toolAdd->setFixedSize( 70,70 );
    connect( m_toolAdd, &CustomGUI::CustomIconButton::clicked,
             this, &PersonListView::clickedAdd );         // Forward buttons signal.
    m_toolChange = new CustomGUI::CustomIconButton( ":svg/change_icon_normal",
                                                    ":svg/change_icon_mover",
                                                    ":svg/change_icon_selected",
                                                    false );
    m_toolChange->setFixedSize(70,70);
    connect( m_toolChange, &CustomGUI::CustomIconButton::clicked,
             this, &PersonListView::clickedChange );      // Forward buttons signal.
    m_toolDelete = new CustomGUI::CustomIconButton( ":svg/delete_icon_normal",
                                                    ":svg/delete_icon_mover",
                                                    ":svg/delete_icon_selected",
                                                    false );
    m_toolDelete->setFixedSize( 70,70 );
    connect( m_toolDelete, &CustomGUI::CustomIconButton::clicked,
             this, &PersonListView::clickedDelete );      // Forward buttons signal.


    /****************************************************************/
    /*********               Widget's Effects:                *******/
    /****************************************************************/
    m_looseFocusEffect = new QGraphicsBlurEffect( this );   // TODO: Evaluate better teamwork of scroll area and this effect.
    m_looseFocusEffect->setBlurRadius( 7 );
    m_looseFocusEffect->setEnabled( false );
    setGraphicsEffect( m_looseFocusEffect );


    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/
    m_listLayout = new QGridLayout();
    m_listLayout->setSpacing( 10 );
    m_listLayout->setContentsMargins( 8, 8, 8, 8 );
    m_listLayout->setSizeConstraint( QLayout::SetMinAndMaxSize );
    mainWidget->setLayout( m_listLayout );

    // Filter tools layout:
    QHBoxLayout* filterToolsLayout = new QHBoxLayout();
    filterToolsLayout->addWidget( m_lblSearchString );
    filterToolsLayout->addWidget( m_leFilterSearchString );
    QGroupBox* filterGroup = new QGroupBox();
    filterGroup->setLayout( filterToolsLayout );

    // Toolbox layout:
    QVBoxLayout* toolboxLayout = new QVBoxLayout();
    toolboxLayout->addWidget( m_toolUpdate );
    toolboxLayout->addWidget( m_toolAdd );
    toolboxLayout->addWidget( m_toolChange );
    toolboxLayout->addWidget( m_toolDelete );

    /*** Main VBox layout. Contains headline, Person list itself (contained within
     *   scroll area and tool bar (for manipulating Person and Person list): ***/
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget( m_headline, 0, 0 );
    mainLayout->addWidget( filterGroup, 1, 0 );
    mainLayout->addWidget( scrollArea, 2, 0 );
    mainLayout->addLayout( toolboxLayout, 2, 1, 1, 1, Qt::AlignTop | Qt::AlignLeft );     // TODO: Implement custom toolbar. Add here.
    setLayout( mainLayout );

    setMinimumWidth( toolboxLayout->minimumSize().width() + mainWidget->minimumWidth() );
    updateDisplayedTexts();
}


PersonListView::~PersonListView()
{
    m_looseFocusEffect = nullptr;
}


/* Public methods: */

void PersonListView::setModel( PersonListViewModel* model )
{
    // Check validity of input pointer. Check whether model changed truely.
    if ( model && model != m_model )
    {
        // If model was already set, disconnect it:
        if ( m_model )
        {
            disconnect( m_model, 0, this, 0 );
        }

        // Apply new model reference:
        m_model = model;
        connect( m_model, &PersonListViewModel::changed,
                 this, &PersonListView::onModelChange );
        onModelChange();
    }
}


bool PersonListView::setPersonSelection( int index )
{
    if ( index < m_personViews.size() )
    {
        PersonView* newSelection = m_personViews.at( index );
        changePersonSelection( newSelection );
        return true;
    } else
    {
        return false;
    }
}


bool PersonListView::visualFocus() const
{
    return !m_looseFocusEffect->isEnabled();
}


void PersonListView::setVisualFocus( bool visualFocus )
{
    if ( m_looseFocusEffect )
        m_looseFocusEffect->setEnabled( !visualFocus );   // If focus shall be set to true, disable blur effect (and vice versa).
}


/* Public slots: */

void PersonListView::updateDisplayedTexts()
{
    // Child widgets:
    TextViewUtilz::SetTextToLabel( m_headline, tr("All Persons") );
    TextViewUtilz::SetTextToLabel( m_lblSearchString, tr("Search:") );

    // Tooltips:
    m_toolUpdate->setToolTip( tr("Update person list") );
    m_toolAdd->setToolTip( tr("Add a new person") );
    m_toolChange->setToolTip( tr("Edit selected person") );
    m_toolDelete->setToolTip( tr("Delete selected person irreversible") );
    m_leFilterSearchString->setToolTip( tr("Enter phrase to search") );

    // Person views:
    foreach ( PersonView* personView, m_personViews )
    {
        personView->updateDisplayedTexts();
    }
}


/* Private methods: */

void PersonListView::changeEvent( QEvent* event )
{
    if ( event->type() == QEvent::LanguageChange )
    {
        updateDisplayedTexts();
    }

    QWidget::changeEvent( event );
}


void PersonListView::changePersonSelection( PersonView* newSelection )
{
    if ( m_selectedPerson ) m_selectedPerson->setState( PersonView::Normal );
    m_selectedPerson = newSelection;
    if ( m_selectedPerson ) m_selectedPerson->setState( PersonView::Focussed );
    emit selectionChanged( m_selectedPerson );
}


/* Private slots: */

void PersonListView::onModelChange()
{
    m_selectedPerson = nullptr;       // Don't know whether selected Person is now invalid.

    // Remove old ones
    foreach ( PersonView* view, m_personViews )
    {
        QPropertyAnimation* awayAnimation = new QPropertyAnimation(view,"windowOpacity",view);
        awayAnimation->setDuration(0);
        awayAnimation->setStartValue(1.0);
        awayAnimation->setEndValue(0.0);

        // Remove andd delete 'view' when animation finished:
        connect( awayAnimation, &QPropertyAnimation::finished,
                 [this, view]() { this->m_listLayout->removeWidget(view); } );
        connect( awayAnimation, &QPropertyAnimation::finished,
                 view, &PersonView::deleteLater );

        awayAnimation->start();
    }
    m_personViews.clear();

    // Insert new ones:
    const int numColumns = 2;
    int row = 0;
    foreach ( PersonViewModel* PersonModel, m_model->modelListFiltered() )
    {
        PersonView* view = new PersonView(m_defaultPalette);
        view->setModel( PersonModel );
        connect( view, &PersonView::mouseClicked, this, &PersonListView::onPersonClicked );
        connect( view, &PersonView::mouseDoubleClicked, this, &PersonListView::onPersonDoubleClicked );
        m_listLayout->addWidget( view, row - (row%numColumns), row%numColumns );
        ++row;
        m_personViews.append( view );
    }
}


void PersonListView::onPersonClicked()
{
    changePersonSelection( qobject_cast<PersonView*>( QObject::sender() ) );
}


void PersonListView::onPersonDoubleClicked()
{
    PersonView* clickedPerson = qobject_cast<PersonView*>( QObject::sender() );
    if ( clickedPerson ) // If cast was successfull, forward signal:
    {
        emit doubleClickedPerson( clickedPerson );
    }
}


} // namespace GUI
} // namespace Dotoo
