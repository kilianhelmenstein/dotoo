#include "personview.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSvgWidget>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QFontMetrics>

#include "customcheckbox.h"
#include "utilz/textviewutilz.h"



namespace Dotoo {
namespace GUI {



PersonView::PersonView( const QPalette &appPalette, QWidget* parent )
    : QWidget( parent ),
      m_model( nullptr ),
      m_state( Normal ),
      m_highlighted( false ),
      m_name( nullptr ),
      m_comment( nullptr ),
      m_personIcon( nullptr )
{
    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/
    QGridLayout* baseLayout = new QGridLayout();
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QHBoxLayout* commentRowLayout = new QHBoxLayout();

    baseLayout->addLayout( commentRowLayout, 0, 0 );
    baseLayout->addLayout( nameLayout, 1, 0 );


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

    m_name = new QLabel();
    m_name->setFont(m_nameFont);

    m_comment = new QLabel();
    m_comment->setFont(m_commentFont);

    m_personIcon = new QSvgWidget( ":/svg/collaboration_icon" );
    m_personIcon->setFixedSize( 22,22);

    nameLayout->addWidget( m_personIcon );
    nameLayout->addWidget( m_name );
    commentRowLayout->addWidget( m_comment );


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
    setAutoFillBackground( true );
    updatePalette();
}


PersonView::~PersonView()
{

}


/* Public methods: */

void PersonView::setModel( PersonViewModel* model )
{
    if ( model && model != m_model )
    {
        if ( m_model )
        {
            disconnect( m_model, 0, this, 0 );
        }

        m_model = model;
        connect( m_model, &PersonViewModel::changed,
                 this, &PersonView::onModelChange );
        connect( m_model, &PersonViewModel::destroyed,
                 this, &PersonView::onModelDeletion );
        onModelChange();
    }
}


void PersonView::setState( State state )
{
    if ( state != m_state ) // Only act if necessary.
    {
        m_state = state;
        updatePalette();
    }
}


void PersonView::setHighlighted( bool highlighted )
{
    if ( highlighted != m_highlighted )
    {
        m_highlighted = highlighted;
        updatePalette();
    }
}


/* Private methods: */

void PersonView::updatePalette()
{
    QPalette newPalette(palette());     // Create new palette, prototyped by my one.
    switch ( state() )
    {
    case Normal:
        newPalette.setColor( QPalette::All, QPalette::Base,
                             highlighted() ? "#ff9eb8e5" : "#ff799cd5" );
        break;
    case Focussed:
        newPalette.setColor( QPalette::All, QPalette::Base,
                             "#ff9eb8e5" );
        break;
    case Disabled:
        newPalette.setColor( QPalette::All, QPalette::Base,                 // 'isDone = false'-presentation
                             "#ffbbc0c8" );
        break;
    }
    setPalette(newPalette);             // Update my palette.
}


/* Private slots: */

void PersonView::onModelChange()
{
    TextViewUtilz::SetTextToLabel( m_name, m_model->getName().fullName() );
    TextViewUtilz::SetTextToLabel( m_comment, m_model->getComment() );
}


void PersonView::onModelDeletion()
{
    m_model = nullptr;
}


} // namespace GUI;
} // namespace Dotoo;
