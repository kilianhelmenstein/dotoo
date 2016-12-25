#include "customiconbutton.h"

#include <QVBoxLayout>
#include <QSvgWidget>



CustomIconButton::CustomIconButton( const QString& iconNormal,
                                    const QString& iconMouseOver,
                                    const QString& iconSelected,
                                    bool selectable,
                                    QWidget* parent )
    : QWidget(parent),
      m_iconNormal(iconNormal),
      m_iconMouseOver(iconMouseOver),
      m_iconSelected(iconSelected),
      m_selectable(selectable),
      m_isSelected(false)
{
    m_icon = new QSvgWidget(m_iconNormal);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->addWidget(m_icon);
    setLayout(layout);
}


void CustomIconButton::mousePressEvent( QMouseEvent* event )
{
    Q_UNUSED(event)
    m_icon->load( QString(m_iconSelected) );
}


void CustomIconButton::mouseReleaseEvent( QMouseEvent* event )
{
    Q_UNUSED(event)

    if ( m_selectable )
    {
        m_isSelected = !m_isSelected;
    }

    // Update presentation:
    if ( m_isSelected )
    {
        m_icon->load( QString(m_iconSelected) );
    } else
    {
         m_icon->load( QString(m_iconNormal) );
    }

    emit clicked( m_isSelected );        // inform listeners
}


void CustomIconButton::enterEvent(QEvent*)
{
    if ( !m_isSelected )
    {
        m_icon->load( QString(m_iconMouseOver) );
    }
}


void CustomIconButton::leaveEvent(QEvent*)
{
    if ( !m_isSelected )
    {
        m_icon->load( QString(m_iconNormal) );
    }
}

