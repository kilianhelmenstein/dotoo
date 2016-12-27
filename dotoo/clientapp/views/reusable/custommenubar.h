#ifndef CUSTOMMENUBAR_H
#define CUSTOMMENUBAR_H

#include <QWidget>
#include <QBoxLayout>



class CustomMenuBar : public QWidget
{
    Q_OBJECT
public:
    /*!
     *\brief    Contains all possible directions for menu bar.
     */
    typedef enum {
        Horizontal  = QBoxLayout::LeftToRight,
        Vertical    = QBoxLayout::TopToBottom
    } Direction;


public:
    /*!
     * \brief   Ctor for CustomMenuBar objects.
     *
     * \param   Direction dir       The direction of the menu bar. Cannot be changed.
     *
     * \param   QWidget* parent     Pointer to parent of new menu bar instance.
     */
    CustomMenuBar( Direction dir,
                   QWidget* parent=nullptr );


    Direction direction() const { return m_dir; }

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

public slots:

private:
    const Direction m_dir;      /*!< Selected direction for this menu bar. */

    QBoxLayout* m_mainLayout;   /*!< Pointer to main layout. Contains the icons. Init. within ctor. */
};

#endif // CUSTOMMENUBAR_H
