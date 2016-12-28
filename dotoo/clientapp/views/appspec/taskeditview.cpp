#include "taskeditview.h"

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


namespace Dotoo {
namespace GUI {


TaskEditView::TaskEditView( const QPalette& appPalette, QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr ),
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
    baseLayout->setLabelAlignment( Qt::AlignRight );

    //baseLayout->addLayout( commentRowLayout, RowIdxComment, ClmnIdxComment );
    //baseLayout->addLayout( subInfoRowLayout, RowIdxSubInformation, ClmnIdxSubInformation );
    //baseLayout->addLayout( buttonsLayout, RowIdxButtons, ClmnIdxButtons );


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
    QFont titleFontBold( m_titleFont );
    titleFontBold.setWeight( m_titleFont.weight() * 1.15 );
    m_lblTitle->setFont( titleFontBold );           // Take a bold-version of title font
    m_lblTitle->setText( tr("Title") );
    m_titleEdit = new QLineEdit();
    m_titleEdit->setFont(m_titleFont);

    m_lblComment = new QLabel();
    QFont commentFontBold( m_commentFont );
    commentFontBold.setWeight( m_commentFont.weight() * 1.2 );
    m_lblComment->setFont( commentFontBold );       // Take a bold-version of comment font
    m_lblComment->setText( tr("Comment") );
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
    m_responsible->addItem( "Kilian Helmenstein" );
    m_responsible->addItem( "Carolin Helmenstein" );

    m_btnAbort = new QPushButton( tr("Abort") );
    connect( m_btnAbort, &QPushButton::clicked,
             this, &TaskEditView::clickedAbort );

    m_btnApply = new QPushButton( tr("Apply") );
    connect( m_btnApply, &QPushButton::clicked,
             this, &TaskEditView::clickedApply );

    baseLayout->addRow( m_lblTitle, m_titleEdit );

    baseLayout->addRow( m_lblComment, m_commentEdit );

    baseLayout->addRow( m_calendarIcon, m_dueDateEdit );

    baseLayout->addRow( m_personIcon, m_responsible );

    baseLayout->addWidget( m_btnAbort );
    baseLayout->addWidget( m_btnApply );


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
    //setMinimumSize( 550, 300 );
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    setBackgroundRole( QPalette::Base );
    setAutoFillBackground( true );
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

QString TaskEditView::title() const { return m_titleEdit->text(); }
QString TaskEditView::comment() const { return m_commentEdit->text(); }
QDate TaskEditView::dueDate() const { return m_dueDateEdit->date(); }
UniqueId TaskEditView::responsible() const { return 0; } // TODO: Use model for this!
UniqueId TaskEditView::creator() const { return 0; } // TODO: Use model for this!


/* Private slots: */

void TaskEditView::onModelChange()
{
    m_titleEdit->setText( m_model->getTitle() );

    m_commentEdit->setText( m_model->getComment() );
    m_dueDateEdit->setDate( m_model->getDueDate() );
}


void TaskEditView::onModelDeletion()
{
    m_model = nullptr;
}


} // namespace GUI;
} // namespace Dotoo;
