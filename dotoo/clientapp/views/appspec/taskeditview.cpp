#include "taskeditview.h"

#include <QEvent>
#include <QFormLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QSvgWidget>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QFontMetrics>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QComboBox>
#include <QStringList>

#include "utilz/textviewutilz.h"
#include "personlistviewmodel.h"
#include "personviewmodel.h"


namespace Dotoo {
namespace GUI {


TaskEditView::TaskEditView( const QPalette& appPalette, QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr ),
      m_personsModel( nullptr ),
      m_lblTitle( nullptr ),
      m_titleEdit( nullptr ),
      m_lblComment( nullptr ),
      m_commentEdit( nullptr ),
      m_calendarIcon( nullptr ),
      m_dueDateEdit( nullptr ),
      m_personIcon( nullptr ),
      m_responsible( nullptr ),
      m_btnAbort( nullptr ),
      m_btnApply( nullptr )
{
    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/
    QFormLayout* baseLayout = new QFormLayout();
    baseLayout->setSizeConstraint( QLayout::SetMaximumSize );
    baseLayout->setLabelAlignment( Qt::AlignRight | Qt::AlignBaseline );


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
    m_lblTitle = new QLabel();
    QFont titleFontBold( m_commentFont );
    titleFontBold.setWeight( m_commentFont.weight() * 1.2 );
    m_lblTitle->setFont( titleFontBold );           // Take a bold-version of title font
    m_titleEdit = new QLineEdit();
    m_titleEdit->setFont(m_titleFont);

    m_lblComment = new QLabel();
    QFont commentFontBold( m_commentFont );
    commentFontBold.setWeight( m_commentFont.weight() * 1.2 );
    m_lblComment->setFont( commentFontBold );       // Take a bold-version of comment font
    m_commentEdit = new QLineEdit();
    m_commentEdit->setFont(m_commentFont);

    m_calendarIcon = new QSvgWidget(":/svg/calendar_icon");
    m_calendarIcon->setFixedSize(20,23);

    m_dueDateEdit = new QDateEdit();
    m_dueDateEdit->setFont(m_subInfoFont);
    //m_dueDateEdit->setMinimumDate( QDate::currentDate() );    // If set, typing date is very unconvinient.

    m_personIcon = new QSvgWidget( ":/svg/collaboration_icon" );
    m_personIcon->setFixedSize( 22,22);
    m_responsible = new QComboBox();
    m_responsible->setFont(m_subInfoFont);

    m_btnAbort = new QPushButton();
    connect( m_btnAbort, &QPushButton::clicked,
             this, &TaskEditView::clickedAbort );

    m_btnApply = new QPushButton();
    connect( m_btnApply, &QPushButton::clicked,
             this, &TaskEditView::clickedApply );

    baseLayout->addRow( m_lblTitle, m_titleEdit );
    baseLayout->addRow( m_lblComment, m_commentEdit );
    baseLayout->addRow( m_calendarIcon, m_dueDateEdit );
    baseLayout->addRow( m_personIcon, m_responsible );

    baseLayout->addRow( m_btnAbort, m_btnApply );


    /****************************************************************/
    /*********               Widget's Effects:                *******/
    /****************************************************************/
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);
    shadow->setBlurRadius(20);
    setGraphicsEffect( shadow );

    setLayout( baseLayout );


    /****************************************************************/
    /*********             Initial Presenation:               *******/
    /****************************************************************/
    setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    setMaximumHeight( 200 );
    setBackgroundRole( QPalette::Base );
    setAutoFillBackground( true );
    updateDisplayedTexts();
}


TaskEditView::~TaskEditView()
{
}


/* Public methods: */

void TaskEditView::setModel( TaskViewModel* model )
{
    if ( model && model != m_model )
    {
        if ( m_model )
        {
            disconnect( m_model, 0, this, 0 );
        }

        m_model = model;
        connect( m_model, &TaskViewModel::destroyed,
                 this, &TaskEditView::onModelDeletion );
        onModelChange();
    }
}


void TaskEditView::setPersonsModel( PersonListViewModel* personsModel )
{
    if ( personsModel && personsModel != m_personsModel )
    {
        if ( m_personsModel )
        {
            disconnect( m_personsModel, 0, this, 0 );
        }

        m_personsModel = personsModel;
        connect( m_personsModel, &PersonListViewModel::changed,
                 this, &TaskEditView::onPersonsModelChange );
        connect( m_personsModel, &PersonListViewModel::destroyed,
                 this, &TaskEditView::onModelDeletion );
        onPersonsModelChange();
    }
}


QString TaskEditView::title() const
{
    return m_titleEdit->text();
}


QString TaskEditView::comment() const
{
    return m_commentEdit->text();
}


QDate TaskEditView::dueDate() const
{
    return m_dueDateEdit->date();
}


UniqueId TaskEditView::responsible() const
{
    return m_responsible->currentData().toInt();
}


UniqueId TaskEditView::creator() const
{
    return 0; // TODO: Use model for this!
}


/* Public slots: */

void TaskEditView::updateDisplayedTexts()
{
    // Child widgets:
    TextViewUtilz::SetTextToLabel( m_lblTitle, tr("Title") );
    TextViewUtilz::SetTextToLabel( m_lblComment, tr("Comment") );
    m_btnAbort->setText( tr("Abort") );
    m_btnApply->setText( tr("Apply") );
}


/* Private slots: */

void TaskEditView::changeEvent( QEvent* event )
{
    if ( event->type() == QEvent::LanguageChange )
    {
        updateDisplayedTexts();
    }

    QWidget::changeEvent( event );
}


void TaskEditView::onModelChange()
{
    if ( !m_model ) return;

    m_titleEdit->setText( m_model->getTitle() );

    m_commentEdit->setText( m_model->getComment() );
    m_dueDateEdit->setDate( m_model->getDueDate() );

    onPersonsModelChange();
}


void TaskEditView::onModelDeletion()
{
    m_model = nullptr;
}


void TaskEditView::onPersonsModelChange()
{
    if ( !m_personsModel ) return;

    m_responsible->setMaxCount(0);
    m_responsible->setMaxCount(m_personsModel->modelList().size());
    foreach ( PersonViewModel* personModel, m_personsModel->modelList() )
    {
        m_responsible->addItem( personModel->getFullName(), personModel->getId() );
    }
}


void TaskEditView::onPersonsModelDeletion()
{
    m_personsModel = nullptr;
}


} // namespace GUI;
} // namespace Dotoo;
