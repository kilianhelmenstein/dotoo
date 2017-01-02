#include "custommenubar.h"

#include <QBoxLayout>

#include "customiconbutton.h"



namespace CustomGUI {



CustomMenuBar::CustomMenuBar( AttachedEdge attachedEdge,
                              int maximumBarWidth,
                              QPalette barPalette,
                              QWidget* parent )
    : QWidget(parent),
      m_attachedEdge(attachedEdge),
      m_mainLayout(nullptr)
{
    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/
    m_mainLayout = new QBoxLayout( static_cast<QBoxLayout::Direction>(attachedEdge) );
    m_mainLayout->setSpacing(0);
    m_mainLayout->setMargin(0);

    m_iconLayout = new QBoxLayout( attachedEdge == Bottom || attachedEdge == Top ? QBoxLayout::LeftToRight
                                                                                 : QBoxLayout::TopToBottom );
    m_iconLayout->setMargin(0);

    QWidget* iconWidget = new QWidget(this);
    iconWidget->setPalette( barPalette );
    iconWidget->setBackgroundRole( QPalette::Background );
    iconWidget->setAutoFillBackground( true );
    if ( m_attachedEdge == Top
         || m_attachedEdge == Bottom )
    {
        iconWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
        iconWidget->setMaximumHeight( maximumBarWidth );
    } else
    {
        iconWidget->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Expanding );
        iconWidget->setMaximumWidth( maximumBarWidth );
    }
    iconWidget->setLayout( m_iconLayout );

    iconWidget->setGeometry( 0, 0, iconWidget->width(), iconWidget->height() );
    m_mainLayout->addWidget( iconWidget );
    setLayout( m_mainLayout );

    /****************************************************************/
    /*********                Widget's Style:                 *******/
    /****************************************************************/
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
                                                         /*selectable:*/ true,
                                                         /*deselectable by mouse:*/ false );
    widgetIcon->setFixedSize( 70, 70 );

    // Add icon to bar:
    m_iconLayout->addWidget( widgetIcon );
    connect( widgetIcon, &CustomIconButton::clicked,
             this, &CustomMenuBar::onIconClicked );

    // Store ref to widget:
    m_menuWidgets.insert( widgetIcon, w );

    // If this is first added menu, make this one visible:
    if ( m_menuWidgets.size() == 1 )
    {
        m_mainLayout->addWidget( w );
        w->setVisible( true );

        m_selectedMenu = m_menuWidgets.begin(); // Selected menu is first (and only) menu
        m_selectedMenu.key()->setSelected( true );
        updateSize();
    }
}


void CustomMenuBar::onIconClicked()
{
    CustomIconButton* sender = qobject_cast<CustomIconButton*>( QObject::sender() );

    QMap<CustomIconButton*, QWidget*>::iterator newSelection = m_menuWidgets.find(sender);
    if ( sender                                     // Check validity of pointer
         && newSelection != m_selectedMenu          // Do nothing if curerntly selected icon was clicked
         && newSelection != m_menuWidgets.end() )   // Pointer isn't null, but it is not valid too!
    {
        // Make selected menu invisible and new selection visible:
        //m_mainLayout->replaceWidget( m_selectedMenu.value(), newSelection.value() );
        m_selectedMenu.key()->setSelected(false);
        m_selectedMenu.value()->setVisible(false);

        m_selectedMenu = newSelection;
        m_selectedMenu.value()->setVisible(true);
        m_selectedMenu.key()->setSelected(true);
    }

    updateSize();
}


void CustomMenuBar::updateSize()
{
    if ( m_attachedEdge == Top
         || m_attachedEdge == Bottom )
    {
        setMaximumSize( m_selectedMenu.value()->maximumWidth(),
                        m_iconLayout->maximumSize().width()
                        + m_selectedMenu.value()->maximumHeight() );
    } else
    {
        setMaximumSize( m_iconLayout->maximumSize().width()
                        + m_selectedMenu.value()->maximumWidth(),
                        m_selectedMenu.value()->maximumHeight() );
    }
}


} // namespace CustomGUI
