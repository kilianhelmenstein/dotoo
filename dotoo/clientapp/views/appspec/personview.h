#ifndef PERSONVIEW_H
#define PERSONVIEW_H


#include <QWidget>

#include "personviewmodel.h"


class QLabel;
class QSvgWidget;


namespace Dotoo {
namespace GUI {


/*!
 * \brief   The PersonView class
 */
class PersonView : public QWidget
{
    Q_OBJECT
public:

    /*!
     * \brief    Contains all possible states of this view.
     */
    typedef enum {
        Normal,     /*!< Normal status. */
        Focussed,   /*!< Selected by user, e.g. */
        Disabled    /*!< Not selectable. */
    } State;

public:
    PersonView( const QPalette& appPalette, QWidget* parent=nullptr );
    virtual ~PersonView();

    /*!
     * \brief   Takes new model instance and updates presentation.
     *
     * \param   TaskViewModel* model        Pointer to new viewmodel instance.
     */
    void setModel( PersonViewModel* model );

    /*!
     * \brief   Delivers the view's model.
     */
    PersonViewModel* model() const { return m_model; }

    /*!
     * \brief   Deliers the widget's state.
     */
    State state() const { return m_state; }

    /*!
     * \brief   Takes the view into desired state. Will update the view and
     *          its state-dependent behavior.
     *
     * \param   State state                 Desired state for this view.
     */
    void setState( State state );

    /*!
     * \brief   Delivers the highlighted state of this widget.
     */
    bool highlighted() const { return m_highlighted; }

    /*!
     * \brief   Sets the highlighted state of this widget.
     *
     * \param   bool highlighted    Indicates whether widget's palette shall be
     *                              selected that it appears highlighted.
     */
    void setHighlighted( bool highlighted );


public slots:
    /*!
     * \brief   Updates all displayed texts (they may depend on selected language).
     */
    void updateDisplayedTexts();

signals:
    void mouseClicked();
    void mouseDoubleClicked();
    void mouseReleased();

protected:
    /*!
     * \brief   Lets widget look highlighted.
     */
    void enterEvent(QEvent*) { setHighlighted(true); updatePalette(); }

    /*!
     * \brief   Lets widget look un-highlighted.
     */
    void leaveEvent(QEvent*) { setHighlighted(false); updatePalette(); }

    /*!
     * \brief   Emit own signal.
     */
    void mousePressEvent(QMouseEvent*) { emit mouseClicked(); }

    /*!
     * \brief   Emit own signal.
     */
    void mouseDoubleClickEvent(QMouseEvent*) { emit mouseDoubleClicked(); }

    /*!
     * \brief   Emit own signal.
     */
    void mouseReleaseEvent(QMouseEvent*) { emit mouseReleased(); }

private:

    /*!
     * \brief   Adapts the widget's palette to 'highlighted' state.
     */
    void updatePalette();


private slots:
    /*!
     * \brief   Handles changes of model's data.
     *
     * \note    See 'setMode()'.
     */
    void onModelChange();

    /*!
     * \brief   Handles the deletion of view's model.
     */
    void onModelDeletion();


private:
    PersonViewModel* m_model;                   /*!< Reference to model that contains presentated data. */
    State m_state;                              /*!< View's current state. */
    bool m_highlighted;                         /*!< Stores highlighted (by mouse over event e.g.) state. */

    // Sub-widgets:
    QLabel* m_forename;
    QLabel* m_name;                             /*!< Displays model's 'title' attribute as text. */
    QLabel* m_comment;                          /*!< Displays model's 'comment' attribute as text. */

    QSvgWidget* m_personIcon;                   /*!< Person icon that leads model's 'responsible person' presentation. */

    // Style:
    QFont m_forenameFont;
    QFont m_nameFont;                           /*!< Font for title. The biggest font. */
    QFont m_commentFont;                        /*!< Font for the comment text. Smaller than title. */
};


} // namespace GUI;
} // namespace Dotoo;

#endif // PERSONVIEW_H
