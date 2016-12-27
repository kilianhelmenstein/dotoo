#include <QSvgWidget>
#include <QVBoxLayout>

#include "customcheckbox.h"



CustomCheckBox::CustomCheckBox( QWidget* parent )
    : QWidget( parent ),
      m_state( false )
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);

    m_icon = new QSvgWidget( ":/svg/checkbox" );
    layout->addWidget( m_icon );

    setLayout( layout );
}


void CustomCheckBox::mouseReleaseEvent( QMouseEvent* event )
{
    Q_UNUSED(event)

    m_state = !m_state;             // toggle state

    // Update presentation:
    if ( m_state )
    {
        m_icon->load( QString(":/svg/checkbox_checked") );
    } else
    {
         m_icon->load( QString(":/svg/checkbox") );
    }

    emit toggled( m_state );        // inform listeners
}
