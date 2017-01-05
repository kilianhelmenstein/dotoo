#include "tasklistview.h"

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

#include "viewmodels/tasklistviewmodel.h"
#include "taskview.h"
#include "utilz/textviewutilz.h"


namespace Dotoo {
namespace GUI {



TaskListView::TaskListView( const QPalette& appPalette,
                            QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr ),
      m_personsModel( nullptr ),
      m_defaultPalette( appPalette ),
      m_listLayout( nullptr ),
      m_toolUpdate( nullptr ),
      m_toolAdd( nullptr ),
      m_toolChange( nullptr ),
      m_toolDelete( nullptr ),
      m_selectedTask( nullptr )
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
    m_lblFilterEnabled = new QLabel();
    m_chbFilterEnabled = new QCheckBox();
    connect( m_chbFilterEnabled, &QCheckBox::toggled,
             this, &TaskListView::filterChanged );

    m_lblFilterIsDone = new QLabel();
    m_lblFilterIsDone->setVisible( m_chbFilterEnabled->isChecked() );
    QObject::connect( m_chbFilterEnabled, &QCheckBox::toggled,
                      m_lblFilterIsDone, &QLabel::setVisible );
    m_cobFilterIsDone = new QComboBox();
    m_cobFilterIsDone->setVisible( m_chbFilterEnabled->isChecked() );
    m_cobFilterIsDone->setEnabled( m_chbFilterEnabled->isChecked() );
    m_cobFilterIsDone->addItem( "", QVariant(true) );   // Text will be set later
    m_cobFilterIsDone->addItem( "", QVariant(false) );  // Text will be set later
    QObject::connect( m_chbFilterEnabled, &QCheckBox::toggled,
                      m_cobFilterIsDone, &QComboBox::setVisible );
    QObject::connect( m_chbFilterEnabled, &QCheckBox::toggled,
                      m_cobFilterIsDone, &QComboBox::setEnabled );
    QObject::connect( m_cobFilterIsDone,
                      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                      this, &TaskListView::filterChanged );

    m_lblSearchString = new QLabel();
    m_leFilterSearchString = new QLineEdit();
    connect( m_leFilterSearchString, &QLineEdit::textChanged,
             this, &TaskListView::filterChanged );

    /*** Task list: ***/
    // Use 'mainWidget' for usage of scroll area (takes only a widget, no layouts):
    QWidget* mainWidget = new QWidget( this );
    mainWidget->setMinimumSize( 600, 500 );             // TODO: Use TaskView's min. size
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
    m_toolUpdate->setFixedSize( ToolboxIconSize, ToolboxIconSize );
    connect( m_toolUpdate, &CustomGUI::CustomIconButton::clicked,
             this, &TaskListView::clickedUpdate );      // Forward buttons signal.
    m_toolAdd = new CustomGUI::CustomIconButton( ":svg/add_icon_normal",
                                                 ":svg/add_icon_mover",
                                                 ":svg/add_icon_selected",
                                                 false );
    m_toolAdd->setFixedSize( ToolboxIconSize, ToolboxIconSize );
    connect( m_toolAdd, &CustomGUI::CustomIconButton::clicked,
             this, &TaskListView::clickedAdd );         // Forward buttons signal.
    m_toolChange = new CustomGUI::CustomIconButton( ":svg/change_icon_normal",
                                                    ":svg/change_icon_mover",
                                                    ":svg/change_icon_selected",
                                                    false );
    m_toolChange->setFixedSize( ToolboxIconSize, ToolboxIconSize );
    connect( m_toolChange, &CustomGUI::CustomIconButton::clicked,
             this, &TaskListView::clickedChange );      // Forward buttons signal.
    m_toolDelete = new CustomGUI::CustomIconButton( ":svg/delete_icon_normal",
                                                    ":svg/delete_icon_mover",
                                                    ":svg/delete_icon_selected",
                                                    false );
    m_toolDelete->setFixedSize( ToolboxIconSize, ToolboxIconSize );
    connect( m_toolDelete, &CustomGUI::CustomIconButton::clicked,
             this, &TaskListView::clickedDelete );      // Forward buttons signal.


    /****************************************************************/
    /*********               Widget's Effects:                *******/
    /****************************************************************/
    m_looseFocusEffect = new QGraphicsBlurEffect( this );   // TODO: Evaluate better teamwork of scroll area and this effect.
    m_looseFocusEffect->setBlurRadius( 15 );
    m_looseFocusEffect->setEnabled( false );
    setGraphicsEffect( m_looseFocusEffect );


    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/
    m_listLayout = new QVBoxLayout();
    m_listLayout->setSpacing( 10 );
    m_listLayout->setContentsMargins( 8, 8, 8, 8 );
    m_listLayout->setSizeConstraint( QLayout::SetMinAndMaxSize );
    mainWidget->setLayout( m_listLayout );

    // Filter tools layout:
    QGridLayout* filterToolsLayout = new QGridLayout();
    filterToolsLayout->addWidget( m_lblFilterEnabled, 0, 0 );
    filterToolsLayout->addWidget( m_chbFilterEnabled, 0, 1, 1, 3 );
    filterToolsLayout->addWidget( m_lblFilterIsDone, 1, 0 );
    filterToolsLayout->addWidget( m_cobFilterIsDone, 1, 1, 1, 3 );
    filterToolsLayout->addWidget( m_lblSearchString, 2, 0 );
    filterToolsLayout->addWidget( m_leFilterSearchString, 2, 1, 1, 3 );
    QGroupBox* filterGroup = new QGroupBox();
    filterGroup->setLayout( filterToolsLayout );


    // Toolbox layout:
    QVBoxLayout* toolboxLayout = new QVBoxLayout();
    toolboxLayout->addWidget( m_toolUpdate );
    toolboxLayout->addWidget( m_toolAdd );
    toolboxLayout->addWidget( m_toolChange );
    toolboxLayout->addWidget( m_toolDelete );

    /*** Main VBox layout. Contains headline, task list itself (contained within
     *   scroll area and tool bar (for manipulating task and task list): ***/
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget( m_headline, 0, 0 );
    mainLayout->addWidget( filterGroup, 1, 0 );
    mainLayout->addWidget( scrollArea, 3, 0 );
    mainLayout->addLayout( toolboxLayout, 3, 1, 1, 1, Qt::AlignTop | Qt::AlignLeft );     // TODO: Implement custom toolbar. Add here.
    setLayout( mainLayout );

    setMinimumWidth( toolboxLayout->minimumSize().width() + mainWidget->minimumWidth() );
    updateDisplayedTexts();
}


TaskListView::~TaskListView()
{
    m_looseFocusEffect = nullptr;
}


/* Public methods: */

void TaskListView::setModel( TaskListViewModel* model )
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
        connect( m_model, &TaskListViewModel::changed,
                 this, &TaskListView::onModelChange );
        onModelChange();
    }
}


bool TaskListView::setTaskSelection( int index )
{
    if ( index < m_taskViews.size() )
    {
        TaskView* newSelection = m_taskViews.at( index );
        changeTaskSelection( newSelection );
        return true;
    } else
    {
        return false;
    }
}


bool TaskListView::visualFocus() const
{
    return !m_looseFocusEffect->isEnabled();
}


void TaskListView::setVisualFocus( bool visualFocus )
{
    if ( m_looseFocusEffect )
    {
        m_looseFocusEffect->setEnabled( !visualFocus );   // If focus shall be set to true, disable blur effect (and vice versa).
    }
}


/* Public slots: */

void TaskListView::updateDisplayedTexts()
{
    // Child widgets:
    TextViewUtilz::SetTextToLabel( m_headline, tr("All Tasks") );
    TextViewUtilz::SetTextToLabel( m_lblFilterEnabled, tr("Enable filter:") );
    TextViewUtilz::SetTextToLabel( m_lblFilterIsDone, tr("Enable filter:") );
    TextViewUtilz::SetTextToLabel( m_lblFilterIsDone, tr("Done:") );
    m_cobFilterIsDone->setItemText( 0, tr("Yes") );
    m_cobFilterIsDone->setItemText( 1, tr("No") );
    TextViewUtilz::SetTextToLabel( m_lblSearchString, tr("Search:") );

    // Tooltips:
    m_toolUpdate->setToolTip( tr("Update task list") );
    m_toolAdd->setToolTip( tr("Add a new task") );
    m_toolChange->setToolTip( tr("Edit selected task") );
    m_toolDelete->setToolTip( tr("Delete selected task irreversible") );
    m_chbFilterEnabled->setToolTip( tr("Enable filtering of task list") );
    m_cobFilterIsDone->setToolTip( tr("Filter done/not done tasks") );
    m_leFilterSearchString->setToolTip( tr("Enter phrase to search") );

    // Person views:
    foreach ( TaskView* taskView, m_taskViews )
    {
        taskView->updateDisplayedTexts();
    }
}


/* Private methods: */

void TaskListView::changeTaskSelection( TaskView* newSelection )
{
    if ( m_selectedTask ) m_selectedTask->setState( TaskView::Normal );
    m_selectedTask = newSelection;
    if ( m_selectedTask ) m_selectedTask->setState( TaskView::Focussed );
    emit selectionChanged( m_selectedTask );
}


/* Private slots: */

void TaskListView::changeEvent( QEvent* event )
{
    if ( event->type() == QEvent::LanguageChange )
    {
        updateDisplayedTexts();
    }

    QWidget::changeEvent( event );
}


void TaskListView::onModelChange()
{
    m_selectedTask = nullptr;       // Don't know whether selected task is now invalid.

    // Remove old ones
    foreach ( TaskView* view, m_taskViews )
    {
        QPropertyAnimation* awayAnimation = new QPropertyAnimation(view,"windowOpacity",view);
        awayAnimation->setDuration(0);
        awayAnimation->setStartValue(1.0);
        awayAnimation->setEndValue(0.0);

        // Remove andd delete 'view' when animation finished:
        connect( awayAnimation, &QPropertyAnimation::finished,
                 [this, view]() { this->m_listLayout->removeWidget(view); } );
        connect( awayAnimation, &QPropertyAnimation::finished,
                 view, &TaskView::deleteLater );

        awayAnimation->start();
    }
    m_taskViews.clear();

    // Insert new ones:
    foreach ( TaskViewModel* taskModel, m_model->modelListFiltered() )
    {
        TaskView* view = new TaskView(m_defaultPalette);
        view->setModel( taskModel );
        view->setPersonsModel( m_personsModel );
        connect( view, &TaskView::mouseClicked, this, &TaskListView::onTaskClicked );
        connect( view, &TaskView::mouseDoubleClicked, this, &TaskListView::onTaskDoubleClicked );
        connect( view, &TaskView::isDoneToggled, this, &TaskListView::onIsDoneTogled );
        m_listLayout->addWidget( view );
        m_taskViews.append( view );
    }
}


void TaskListView::onTaskClicked()
{
    changeTaskSelection( qobject_cast<TaskView*>( QObject::sender() ) );
}


void TaskListView::onTaskDoubleClicked()
{
    TaskView* clickedTask = qobject_cast<TaskView*>( QObject::sender() );
    if ( clickedTask ) // If cast was successfull, forward signal:
    {
        emit doubleClickedTask( clickedTask );
    }
}


void TaskListView::onIsDoneTogled( bool isDone )
{
    TaskView* impactedTask = qobject_cast<TaskView*>( QObject::sender() );
    if ( impactedTask ) // If cast was successfull, forward signal:
    {
        emit isDoneToggled( impactedTask, isDone );
    }
}


} // namespace GUI
} // namespace Dotoo
