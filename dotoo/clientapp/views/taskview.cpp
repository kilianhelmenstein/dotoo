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



using namespace Dotoo;



TaskView::TaskView( QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr )
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
    QPalette* myPalette = new QPalette();
    myPalette->setColor( QPalette::All, QPalette::Base, "#ffde6d6a" );
    myPalette->setColor( QPalette::All, QPalette::Light, "#ff8fdb9b" );
    myPalette->setColor( QPalette::All, QPalette::Text, "black" );
    setPalette( *myPalette );


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
    m_checkBox = new CustomCheckBox();
    m_checkBox->setFixedSize( 55, 55 );
    connect( m_checkBox, &CustomCheckBox::toggled, this, &TaskView::isDoneToggled );
    m_title = new QLabel();
    m_title->setFont(m_titleFont);
    connect( m_checkBox, &CustomCheckBox::toggled, this, &TaskView::onCheckBoxStateChange );

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
    setFixedSize( 550, 115 );

    setBackgroundRole( QPalette::Base );
    setAutoFillBackground( true );
}


TaskView::~TaskView()
{

}


/* Public methods: */

void TaskView::setModel( TaskViewModel* model )
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
    setBackgroundRole( isDone ? QPalette::Dark : QPalette::Base );

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
    TextViewUtilz::SetTextToLabel( m_title, "Lorem ipsum Lorem ipsum Lorem ipsum Lorem ipsum Lorem ipsum Lorem ipsum" );
    TextViewUtilz::SetTextToLabel( m_comment, m_model->getComment() );
    TextViewUtilz::SetTextToLabel( m_dueDate, QDate::currentDate().toString() );
    TextViewUtilz::SetTextToLabel( m_responsible, "Carolin Helmenstein" );

    // Update 'isDone' depending presentation:
    changeIsDonePresentation( m_model->isDone() );
}


void TaskView::onCheckBoxStateChange( bool state )
{
    emit isDoneToggled( state );       // Forward signal: Contoller has to handle it.

    // Change presentation immediatly for better user feeling:
    changeIsDonePresentation( state );
}
