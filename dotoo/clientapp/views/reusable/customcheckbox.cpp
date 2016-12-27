#include <QSvgWidget>
#include <QVBoxLayout>

#include "customcheckbox.h"


namespace CustomGUI {



CustomCheckBox::CustomCheckBox( bool defaultState, QWidget* parent )
    : QWidget( parent ),
      m_state( defaultState )
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);

    m_icon = new QSvgWidget();
    layout->addWidget( m_icon );
    setState( m_state );

    setLayout( layout );
}


void CustomCheckBox::setState( bool state )
{
    m_state = state;

    // Update presentation:
    if ( m_state )
    {
        m_icon->load( QString(":/svg/checkbox_checked") );
    } else
    {
        m_icon->load( QString(":/svg/checkbox") );
    }

}


void CustomCheckBox::mouseReleaseEvent( QMouseEvent* )
{
    setState( !state() );
    emit toggled( m_state );        // inform listeners
}


} // namespace CustomGUI
