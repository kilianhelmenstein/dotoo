#include "custommenubar.h"

#include <QBoxLayout>

#include "customiconbutton.h"



namespace CustomGUI {



CustomMenuBar::CustomMenuBar( Direction dir,
                              QWidget* parent )
    : QWidget(parent),
      m_dir(dir),
      m_mainLayout(nullptr)
{
    m_mainLayout = new QBoxLayout( static_cast<QBoxLayout::Direction>(dir) );
    m_mainLayout->setSpacing(0);
    m_mainLayout->setMargin(0);

    m_iconLayout = new QBoxLayout( dir == Horizontal ? QBoxLayout::TopToBottom
                                                     : QBoxLayout::LeftToRight );
    m_iconLayout->setMargin(0);

    m_mainLayout->addLayout( m_iconLayout );
    setLayout( m_mainLayout );
}


void CustomMenuBar::addWidget( QWidget* w,
                               const QString& iconNormal,
                               const QString &iconMouseOver,
                               const QString &iconSelected )
{
    // Create new icon that represents widget in bar:
    CustomIconButton* widgetIcon = new CustomIconButton( iconNormal,
                                                         iconMouseOver,
                                                         iconSelected,
                                                         /*selectable:*/ false,
                                                         /*parent:*/ this );
    widgetIcon->setFixedSize( 70,70 );

    // Add icon to bar:
    m_iconLayout->addWidget( widgetIcon );
    connect( widgetIcon, &CustomIconButton::clicked,
             this, &CustomMenuBar::onIconClicked );

    // Store ref to widget:
    m_menuWidgets.insert( widgetIcon, w );
    if ( m_menuWidgets.size() == 1 )
    {
        m_mainLayout->addWidget( w );
        w->setVisible( true );
    }
}


void CustomMenuBar::onIconClicked()
{
    CustomIconButton* sender = qobject_cast<CustomIconButton*>( QObject::sender() );

    if ( sender && m_menuWidgets.contains(sender) )
    {
        foreach ( QWidget* menuWidget, m_menuWidgets )
        {
            menuWidget->setVisible(false);
        }
        m_menuWidgets[sender]->setVisible(true);
        sender->setSelected(true);
    }
}


} // namespace CustomGUI
