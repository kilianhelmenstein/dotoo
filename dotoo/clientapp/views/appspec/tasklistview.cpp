#include "tasklistview.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QRadialGradient>
#include <QSizePolicy>
#include <QLabel>
#include <QPropertyAnimation>
#include <QCheckBox>
#include <QComboBox>

#include "customiconbutton.h"

#include "viewmodels/tasklistviewmodel.h"
#include "taskview.h"
#include "utilz/textviewutilz.h"


namespace Dotoo {
namespace GUI {



TaskListView::TaskListView( const QString headlineText,
                            const QPalette& appPalette,
                            QWidget* parent )
    : QWidget( parent) ,
      m_model( nullptr ),
      m_defaultPalette( appPalette ),
      m_listLayout( nullptr ),
      m_selectedTask( nullptr )
{  
    /****************************************************************/
    /*********             Initial Presenation:               *******/
    /****************************************************************/
    setMinimumSize( 600, 500 );
    setMaximumSize( 700, 2000 );
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
    headlineFont.setPointSize( 40 );
    headlineFont.setStyleHint( QFont::SansSerif );
    headlineFont.setWeight( 30 );
    m_headline = new QLabel();
    m_headline->setFont( headlineFont );
    m_headline->setText( headlineText );

    /*** Filter selection: ***/
    m_filterEnabled = new QCheckBox();
    connect( m_filterEnabled, &QCheckBox::toggled,
             this, &TaskListView::filterChanged );

    QLabel* lblFilterIsDone = new QLabel( "Erledigt:" );
    m_filterIsDone = new QComboBox();
    m_filterIsDone->addItem( "Ja", QVariant(true) );
    m_filterIsDone->addItem( "Nein", QVariant(false) );
    QObject::connect( m_filterIsDone,
                      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                      this, &TaskListView::filterChanged );

    QLabel* lblSearchString = new QLabel( "Suchbegriff:" );
    m_filterSearchString = new QLineEdit();
    connect( m_filterSearchString, &QLineEdit::textChanged,
             this, &TaskListView::filterChanged );

    /*** Task list: ***/
    // Use 'mainWidget' for usage of scroll area (takes only a widget, no layouts):
    QWidget* mainWidget = new QWidget( this );
    mainWidget->setMinimumSize( 600, 500 );             // TODO: Use TaskView's min. size
    mainWidget->setMaximumSize( 700, 2000 );            // TODO: Evaluate better size hints
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
    CustomGUI::CustomIconButton* toolUpdate = new CustomGUI::CustomIconButton( ":svg/update_icon_normal",
                                                                               ":svg/update_icon_mover",
                                                                               ":svg/update_icon_selected",
                                                                               false );
    toolUpdate->setFixedSize( 70,70 );
    connect( toolUpdate, &CustomGUI::CustomIconButton::clicked,
             this, &TaskListView::clickedUpdate );      // Forward buttons signal.
    CustomGUI::CustomIconButton* toolAdd = new CustomGUI::CustomIconButton( ":svg/add_icon_normal",
                                                                            ":svg/add_icon_mover",
                                                                            ":svg/add_icon_selected",
                                                                            false );
    toolAdd->setFixedSize( 70,70 );
    connect( toolAdd, &CustomGUI::CustomIconButton::clicked,
             this, &TaskListView::clickedAdd );         // Forward buttons signal.
    CustomGUI::CustomIconButton* toolChange = new CustomGUI::CustomIconButton( ":svg/change_icon_normal",
                                                                               ":svg/change_icon_mover",
                                                                               ":svg/change_icon_selected",
                                                                               false );
    toolChange->setFixedSize(70,70);
    connect( toolChange, &CustomGUI::CustomIconButton::clicked,
             this, &TaskListView::clickedChange );      // Forward buttons signal.
    CustomGUI::CustomIconButton* toolDelete = new CustomGUI::CustomIconButton( ":svg/delete_icon_normal",
                                                                               ":svg/delete_icon_mover",
                                                                               ":svg/delete_icon_selected",
                                                                               false );
    toolDelete->setFixedSize( 70,70 );
    connect( toolDelete, &CustomGUI::CustomIconButton::clicked,
             this, &TaskListView::clickedDelete );      // Forward buttons signal.


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
    m_listLayout = new QVBoxLayout();
    m_listLayout->setSpacing( 10 );
    m_listLayout->setSizeConstraint( QLayout::SetMinAndMaxSize );
    mainWidget->setLayout( m_listLayout );

    // Filter tools layout:
    QHBoxLayout* filterToolsLayout = new QHBoxLayout();
    filterToolsLayout->addWidget( m_filterEnabled );
    filterToolsLayout->addWidget( lblFilterIsDone );
    filterToolsLayout->addWidget( m_filterIsDone );
    filterToolsLayout->addWidget( lblSearchString );
    filterToolsLayout->addWidget( m_filterSearchString );

    // Toolbox layout:
    QVBoxLayout* toolboxLayout = new QVBoxLayout();
    toolboxLayout->addWidget( toolUpdate );
    toolboxLayout->addWidget( toolAdd );
    toolboxLayout->addWidget( toolChange );
    toolboxLayout->addWidget( toolDelete );

    /*** Main VBox layout. Contains headline, task list itself (contained within
     *   scroll area and tool bar (for manipulating task and task list): ***/
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget( m_headline, 0, 0 );
    mainLayout->addLayout( filterToolsLayout, 1, 0 );
    mainLayout->addWidget( scrollArea, 2, 0 );
    mainLayout->addLayout( toolboxLayout, 2, 1, 1, 1, Qt::AlignTop | Qt::AlignLeft );     // TODO: Implement custom toolbar. Add here.
    setLayout( mainLayout );

    setMinimumWidth( toolboxLayout->minimumSize().width() + mainWidget->minimumWidth() );
}


TaskListView::~TaskListView()
{
}


/* Public methods: */

void TaskListView::setHeadline( const QString& headlineText )
{
    TextViewUtilz::SetTextToLabel( m_headline, headlineText );
}


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
    m_looseFocusEffect->setEnabled( !visualFocus );   // If focus shall be set to true, disable blur effect (and vice versa).
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
