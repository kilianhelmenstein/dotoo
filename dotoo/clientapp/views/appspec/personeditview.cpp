#include "personeditview.h"

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


namespace Dotoo {
namespace GUI {


PersonEditView::PersonEditView( const QPalette& appPalette, QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr ),
      m_personIcon( nullptr ),
      m_lblForename( nullptr ),
      m_forenameEdit( nullptr ),
      m_lblName( nullptr ),
      m_nameEdit( nullptr ),
      m_lblComment( nullptr ),
      m_commentEdit( nullptr ),
      m_btnAbort( nullptr ),
      m_btnApply( nullptr )
{
    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/
    QFormLayout* baseLayout = new QFormLayout();
    baseLayout->setLabelAlignment( Qt::AlignRight );


    /****************************************************************/
    /*********                Widget's Style:                 *******/
    /****************************************************************/
    // Init widget color system:
    setPalette(appPalette);

    // Init fonts:
    m_nameFont.setPointSize(35);
    m_nameFont.setStyleHint(QFont::SansSerif);
    m_nameFont.setWeight(30);

    m_commentFont.setPointSize(12);
    m_commentFont.setWeight(50);


    /****************************************************************/
    /*********             Widget's sub-widgets:              *******/
    /****************************************************************/
    m_lblForename = new QLabel();
    QFont nameFontBold( m_nameFont );
    nameFontBold.setPointSize(20);
    nameFontBold.setWeight( m_nameFont.weight() * 1.05 );
    m_lblForename->setFont( nameFontBold );     // Take a bold-version of title font
    m_forenameEdit = new QLineEdit();
    m_forenameEdit->setFont(m_nameFont);

    m_lblName = new QLabel();
    m_lblName->setFont( nameFontBold );         // Take a bold-version of title font
    m_nameEdit = new QLineEdit();
    m_nameEdit->setFont(m_nameFont);

    m_lblComment = new QLabel();
    QFont commentFontBold( m_commentFont );
    commentFontBold.setWeight( m_commentFont.weight() * 1.2 );
    m_lblComment->setFont( commentFontBold );       // Take a bold-version of comment font
    m_commentEdit = new QLineEdit();
    m_commentEdit->setFont(m_commentFont);

    m_personIcon = new QSvgWidget( ":/svg/collaboration_icon" );
    m_personIcon->setFixedSize( 40, 40 );

    m_btnAbort = new QPushButton();
    connect( m_btnAbort, &QPushButton::clicked,
             this, &PersonEditView::clickedAbort );

    m_btnApply = new QPushButton();
    connect( m_btnApply, &QPushButton::clicked,
             this, &PersonEditView::clickedApply );

    //baseLayout->addWidget( m_personIcon );
    baseLayout->addRow( m_lblForename, m_forenameEdit );
    baseLayout->addRow( m_lblName, m_nameEdit );
    baseLayout->addRow( m_lblComment, m_commentEdit );

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
    setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    setBackgroundRole( QPalette::Background );
    setAutoFillBackground( true );
    updateDisplayedTexts();
}


PersonEditView::~PersonEditView()
{
}


/* Public methods: */

void PersonEditView::setModel( PersonViewModel* model )
{
    if ( model && model != m_model )
    {
        if ( m_model )
        {
            disconnect( m_model, 0, this, 0 );
        }

        m_model = model;
        connect( m_model, &PersonViewModel::destroyed,
                 this, &PersonEditView::onModelDeletion );
        onModelChange();
    }
}


QString PersonEditView::name() const
{
    return m_nameEdit->text();
}


QString PersonEditView::forename() const
{
    return m_forenameEdit->text();
}


QString PersonEditView::comment() const
{
    return m_commentEdit->text();
}


/* Public slots: */

void PersonEditView::updateDisplayedTexts()
{
    // Child widgets:
    TextViewUtilz::SetTextToLabel( m_lblForename, tr("Forename") );
    TextViewUtilz::SetTextToLabel( m_lblName, tr("Name") );
    TextViewUtilz::SetTextToLabel( m_lblComment, tr("Comment") );
    m_btnAbort->setText( tr("Abort") );
    m_btnApply->setText( tr("Apply") );
}


/* Private slots: */

void PersonEditView::changeEvent( QEvent* event )
{
    if ( event->type() == QEvent::LanguageChange )
    {
        updateDisplayedTexts();
    }

    QWidget::changeEvent( event );
}


void PersonEditView::onModelChange()
{
    m_forenameEdit->setText( m_model->getName().forename );
    m_nameEdit->setText( m_model->getName().name );

    m_commentEdit->setText( m_model->getComment() );
}


void PersonEditView::onModelDeletion()
{
    m_model = nullptr;
}


} // namespace GUI;
} // namespace Dotoo;
