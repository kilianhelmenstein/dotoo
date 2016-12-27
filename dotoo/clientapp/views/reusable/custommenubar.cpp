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
                                                         /*selectable:*/ true,
                                                         /*parent:*/ this );

    // Add icon to bar:
    m_mainLayout->addWidget( widgetIcon );

    // Store ref to widget:

}


} // namespace CustomGUI
