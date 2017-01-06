#include "taskview.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QSvgWidget>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QFontMetrics>

#include "customcheckbox.h"
#include "personlistviewmodel.h"
#include "personviewmodel.h"
#include "utilz/textviewutilz.h"



namespace Dotoo {
namespace GUI {



TaskView::TaskView( const QPalette &appPalette, QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr ),
      m_personsModel( nullptr ),
      m_state( Normal ),
      m_highlighted( false ),
      m_checkBox( nullptr ),
      m_title( nullptr ),
      m_comment( nullptr ),
      m_calendarIcon( nullptr ),
      m_dueDate( nullptr ),
      m_personIcon( nullptr ),
      m_responsible( nullptr )
{
    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/
    QGridLayout* baseLayout = new QGridLayout();
    QHBoxLayout* commentRowLayout = new QHBoxLayout();
    QHBoxLayout* subInfoRowLayout = new QHBoxLayout();

    baseLayout->addLayout( commentRowLayout, RowIdxComment, ClmnIdxComment, 1, 1, Qt::AlignVCenter);
    baseLayout->addLayout( subInfoRowLayout, RowIdxSubInformation, ClmnIdxSubInformation );

    /****************************************************************/
    /*********                Widget's Style:                 *******/
    /****************************************************************/
    // Init widget color system:
    setPalette(appPalette);

    // Init fonts:
    m_titleFont.setPointSize(20);
    m_titleFont.setStyleHint(QFont::SansSerif);
    m_titleFont.setWeight(30);

    m_commentFont.setPointSize(11);
    m_commentFont.setWeight(50);

    m_subInfoFont.setPointSize(11);
    m_subInfoFont.setWeight(50);


    /****************************************************************/
    /*********             Widget's sub-widgets:              *******/
    /****************************************************************/
    m_checkBox = new CustomGUI::CustomCheckBox();
    m_checkBox->setFixedSize( 45, 45 );
    connect( m_checkBox, &CustomGUI::CustomCheckBox::toggled, this, &TaskView::onCheckBoxStateChange );

    m_title = new QLabel();
    m_title->setFont(m_titleFont);
    m_title->setWordWrap(true);

    m_comment = new QLabel();
    m_comment->setFont(m_commentFont);

    m_calendarIcon = new QSvgWidget(":/svg/calendar_icon");
    m_calendarIcon->setFixedSize(20,23);

    m_dueDate = new QLabel();
    m_dueDate->setFont(m_subInfoFont);

    m_personIcon = new QSvgWidget( ":/svg/collaboration_icon" );
    m_personIcon->setFixedSize( 22,22);
    m_responsible = new QLabel();
    m_responsible->setFont(m_subInfoFont);

    baseLayout->addWidget( m_checkBox, RowIdxMain, ClmnIdxCheckBox, 3, 1 );
    baseLayout->addWidget( m_title, RowIdxMain, ClmnIdxTitle );
    commentRowLayout->addWidget( m_comment );
    subInfoRowLayout->addWidget( m_calendarIcon );
    subInfoRowLayout->addWidget( m_dueDate );
    subInfoRowLayout->addWidget( m_personIcon );
    subInfoRowLayout->addWidget( m_responsible );


    /****************************************************************/
    /*********               Widget's Effects:                *******/
    /****************************************************************/
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(2,2);
    shadow->setBlurRadius(12);
    setGraphicsEffect( shadow );

    setLayout( baseLayout );


    /****************************************************************/
    /*********             Initial Presenation:               *******/
    /****************************************************************/
    setBackgroundRole( QPalette::Base );
    setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Minimum );
    setAutoFillBackground( true );
    updatePalette();
}


TaskView::~TaskView()
{

}


/* Public methods: */

void TaskView::setModel( TaskViewModel* model )
{
    if ( model && model != m_model )
    {
        if ( m_model )
        {
            disconnect( m_model, 0, this, 0 );
        }

        m_model = model;
        connect( m_model, &TaskViewModel::changed,
                 this, &TaskView::onModelChange );
        connect( m_model, &TaskViewModel::destroyed,
                 this, &TaskView::onModelDeletion );
        onModelChange();
    }
}


void TaskView::setPersonsModel( PersonListViewModel* personsModel )
{
    if ( personsModel && personsModel != m_personsModel )
    {
        if ( m_personsModel )
        {
            disconnect( m_personsModel, 0, this, 0 );
        }

        m_personsModel = personsModel;
        connect( m_personsModel, &PersonListViewModel::changed,
                 this, &TaskView::onPersonsModelChange );
        connect( m_personsModel, &PersonListViewModel::destroyed,
                 this, &TaskView::onPersonsModelChange );
        onModelChange();
    }
}


void TaskView::setState( State state )
{
    if ( state != m_state ) // Only act if necessary.
    {
        m_state = state;
        m_checkBox->setEnabled( m_state != Disabled );  // Disable if necessary.
        updatePalette();
    }
}


void TaskView::setHighlighted( bool highlighted )
{
    if ( highlighted != m_highlighted )
    {
        m_highlighted = highlighted;
        updatePalette();
    }
}


/* Private methods: */

void TaskView::updatePalette()
{
    QPalette newPalette(palette());     // Create new palette, prototyped by my one.
    switch ( state() )
    {
    case Normal:
        newPalette.setColor( QPalette::All, QPalette::Base,                 // 'isDone = false'-presentation
                             highlighted() ? "#ffdd8f8d" : "#ffd8807d" );
        newPalette.setColor( QPalette::All, QPalette::AlternateBase,        // 'isDone = true'-presentation
                             highlighted() ? "#ffc5e4c8" : "#ffb0d7b4" );
        break;
    case Focussed:
        newPalette.setColor( QPalette::All, QPalette::Base,                 // 'isDone = false'-presentation
                             "#fffda4a0" );
        newPalette.setColor( QPalette::All, QPalette::AlternateBase,        // 'isDone = true'-presentation
                             "#ffdbfede" );
        break;
    case Disabled:
        newPalette.setColor( QPalette::All, QPalette::Base,                 // 'isDone = false'-presentation
                             "#ffc89695" );
        newPalette.setColor( QPalette::All, QPalette::AlternateBase,        // 'isDone = true'-presentation
                             "#ff99b99e" );
        break;
    }
    setPalette(newPalette);             // Update my palette.
}

void TaskView::setSubInfoVisible( bool visible )
{
    m_comment->setVisible( visible );
    m_calendarIcon->setVisible( visible );
    m_dueDate->setVisible( visible );
    m_personIcon->setVisible( visible );
    m_responsible->setVisible( visible );
}


void TaskView::changeIsDonePresentation( bool isDone )
{
    m_checkBox->setState( isDone );     // Update checkbox

    // Change backround color:
    setBackgroundRole( isDone ? QPalette::AlternateBase : QPalette::Base );

    // Strike out title if isDone is true:
    m_titleFont.setStrikeOut(isDone);
    m_title->setFont(m_titleFont);
    m_title->setWordWrap(!isDone);

    // Size depends on checkbox state:
    if ( isDone )
    {
        setMinimumSize( 550, 60 );
        setMaximumSize( 800, 60 );
    } else
    {
        setMinimumSize( 550, 100 );
        setMaximumSize( 800, 300 );
    }

    // Sub info (comment, due date, responsible person)
    setSubInfoVisible( !isDone );
}


/* Private slots: */

void TaskView::resizeEvent( QResizeEvent* )
{
    //onModelChange();
}

void TaskView::onModelChange()
{
    if ( !m_model ) return;

    // Update 'isDone'-dependent presentation:
    changeIsDonePresentation( m_model->isDone() );

    TextViewUtilz::SetTextToLabel( m_title, m_model->getTitle() );
    TextViewUtilz::SetTextToLabel( m_comment, m_model->getComment() );
    if ( m_comment->isVisible() ) m_comment->setHidden( m_comment->text().isEmpty() );
    TextViewUtilz::SetTextToLabel( m_dueDate, m_model->getDueDate().toString() );
    onPersonsModelChange();

}


void TaskView::onModelDeletion()
{
    m_model = nullptr;
}


void TaskView::onPersonsModelChange()
{
    if ( !m_personsModel ) return;

    // Get right person model:
    PersonViewModel* myPersonModel = nullptr;
    foreach ( PersonViewModel* personModel, m_personsModel->modelList() )
    {
        if ( personModel->getId() == m_model->getResponsible() )
        {
            myPersonModel = personModel;
            break;
        }
    }

    // If model could be found, set label:
    if ( myPersonModel )
    {
        TextViewUtilz::SetTextToLabel( m_responsible, myPersonModel->getFullName() );
    } else
    {
        m_responsible->setText("-");    // Sign for user: no responsible selected
    }
}


void TaskView::onPersonsModelDeletion()
{
    m_personsModel = nullptr;
}


void TaskView::onCheckBoxStateChange( bool state )
{
    emit isDoneToggled( state );       // Forward signal: Contoller has to handle it.

    // Change presentation immediatly (for better user experience):
    changeIsDonePresentation( state );
}


} // namespace GUI;
} // namespace Dotoo;
