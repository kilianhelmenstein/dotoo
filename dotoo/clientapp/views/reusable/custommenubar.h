#ifndef CUSTOMMENUBAR_H
#define CUSTOMMENUBAR_H

#include <QWidget>
#include <QMap>
#include <QBoxLayout>



namespace CustomGUI {

class CustomIconButton;


/*!
 * \brief   The CustomMenuBar class implements a bar of icons, where every icon represents
 *          a selectable menu
 */
class CustomMenuBar : public QWidget
{
    Q_OBJECT
public:
    /*!
     *\brief    Contains all possible edges for menu bar.
     */
    typedef enum {
        Left    = QBoxLayout::LeftToRight,
        Right   = QBoxLayout::RightToLeft,
        Top     = QBoxLayout::TopToBottom,
        Bottom  = QBoxLayout::BottomToTop
    } AttachedEdge;


public:
    /*!
     * \brief   Ctor for CustomMenuBar objects.
     *
     * \param   Direction dir       The direction of the menu bar. Cannot be changed.
     *
     * \param   QPalette barPalette Palette used for this menu bar.
     *
     * \param   QWidget* parent     Pointer to parent of new menu bar instance.
     */
    CustomMenuBar( AttachedEdge attachedEdge,
                   int maximumBarWidth,
                   QPalette barPalette,
                   QWidget* parent=nullptr );


    AttachedEdge direction() const { return m_attachedEdge; }

    /*!
     * \brief   Adds a new icon to menu bar that represents the widget referenced by
     *          'w'.
     *
     * \param   QWidget* w                      Reference to represented widget that can be selected through
     *                                          menu bar.
     *
     * \param   const QString& iconNormal       Menu bar icon for normal state.
     *
     * \param   const QString& iconMouseOver    Menu bar icon for mouse over state.
     *
     * \param   const QString& iconSelected     Menu bar icon for selected state.
     */
    void addWidget( QWidget* w,
                    const QString& iconNormal,
                    const QString& iconMouseOver,
                    const QString& iconSelected );

signals:
    /*!
     * \brief   This signal is emitted when user changed menu selection.
     *
     * \param   QWidget* selectedWidget     Pointer to now selected widget.
     */
    void selectionChanged( QWidget* selectedWidget );

private slots:
    /*!
     * \brief   Handles click on an icon: Change menu selection if necessary.
     */
    void onIconClicked();

private:
    /*!
     * \brief   Updates the maximum size (depending on current menu).
     */
    void updateSize();

private:
    const AttachedEdge m_attachedEdge;                  /*!< Selected direction for this menu bar. */

    QBoxLayout* m_mainLayout;   /*!< Pointer to main layout. Contains icon bar and the menu widgets. */
    QBoxLayout* m_iconLayout;   /*!< Pointer to layout that manages icon */

    int m_maxIconSize;

    QMap<CustomIconButton*, QWidget*> m_menuWidgets;    /*!< List with references to all selectable */
    QMap<CustomIconButton*, QWidget*>::iterator m_selectedMenu; /*!< Currently selected menu widget. */
};


} // namespace CustomGUI

#endif // CUSTOMMENUBAR_H
