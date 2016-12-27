#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QSvgWidget>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QFontMetrics>

#include "taskview.h"
#include "customcheckbox.h"

#include "utilz/textviewutilz.h"



namespace Dotoo {
namespace GUI {



TaskView::TaskView( const QPalette &appPalette, QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr ),
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

    baseLayout->addLayout( commentRowLayout, RowIdxComment, ClmnIdxComment );
    baseLayout->addLayout( subInfoRowLayout, RowIdxSubInformation, ClmnIdxSubInformation );


    /****************************************************************/
    /*********                Widget's Style:                 *******/
    /****************************************************************/
    // Init widget color system:
    setPalette(appPalette);

    // Init fonts:
    m_titleFont.setPointSize(35);
    m_titleFont.setStyleHint(QFont::SansSerif);
    m_titleFont.setWeight(30);

    m_commentFont.setPointSize(12);
    m_commentFont.setWeight(50);

    m_subInfoFont.setPointSize(12);
    m_subInfoFont.setWeight(50);


    /****************************************************************/
    /*********             Widget's sub-widgets:              *******/
    /****************************************************************/
    m_checkBox = new CustomGUI::CustomCheckBox();
    m_checkBox->setFixedSize( 60, 60 );
    connect( m_checkBox, &CustomGUI::CustomCheckBox::toggled, this, &TaskView::isDoneToggled );
    m_title = new QLabel();
    m_title->setFont(m_titleFont);
    connect( m_checkBox, &CustomGUI::CustomCheckBox::toggled, this, &TaskView::onCheckBoxStateChange );

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
    shadow->setBlurRadius(8);
    setGraphicsEffect( shadow );

    setLayout( baseLayout );


    /****************************************************************/
    /*********             Initial Presenation:               *******/
    /****************************************************************/
    setMinimumSize( 550, 115 );
    setMaximumSize( 580, 135 );
    setBackgroundRole( QPalette::Base );
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
                             highlighted() ? "#ffe69290" : "#ffde6d6a" );
        newPalette.setColor( QPalette::All, QPalette::AlternateBase,        // 'isDone = true'-presentation
                             highlighted() ? "#ffbfeac4" : "#ff8fdb9b" );
        break;
    case Focussed:
        newPalette.setColor( QPalette::All, QPalette::Base,                 // 'isDone = false'-presentation
                             "#ffe69290" );
        newPalette.setColor( QPalette::All, QPalette::AlternateBase,        // 'isDone = true'-presentation
                             "#ffbfeac4" );
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
    // Change backround color:
    setBackgroundRole( isDone ? QPalette::AlternateBase : QPalette::Base );

    // Strike out title if isDone is true:
    m_titleFont.setStrikeOut(isDone);
    m_title->setFont(m_titleFont);

    // Size depends on checkbox state:
    if ( isDone )
    {
        setFixedSize( 550, 75 );
    } else
    {
        setFixedSize( 550, 115 );
    }

    // Sub info (comment, due date, responsible person)
    setSubInfoVisible( !isDone );
}


/* Private slots: */

void TaskView::onModelChange()
{
    if ( !m_model->getTitle().isEmpty() ) TextViewUtilz::SetTextToLabel( m_title, m_model->getTitle() );
    else m_title->setText( "Server not reachable" );    // remove later, only for development
    TextViewUtilz::SetTextToLabel( m_comment, m_model->getComment() );
    TextViewUtilz::SetTextToLabel( m_dueDate, QDate::currentDate().toString() );
    TextViewUtilz::SetTextToLabel( m_responsible, "Carolin Helmenstein" );

    // Update 'isDone'-dependent presentation:
    changeIsDonePresentation( m_model->isDone() );
}


void TaskView::onCheckBoxStateChange( bool state )
{
    emit isDoneToggled( state );       // Forward signal: Contoller has to handle it.

    // Change presentation immediatly (for better user experience):
    changeIsDonePresentation( state );
}



} // namespace GUI;
} // namespace Dotoo;
