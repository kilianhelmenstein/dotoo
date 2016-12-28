#ifndef TASKVIEW_H
#define TASKVIEW_H

#include <QWidget>
#include <QFont>


class QGridLayout;
class QHBoxLayout;
class QLabel;
class QSvgWidget;
class QPalette;


#include "customcheckbox.h"
#include "taskviewmodel.h"


namespace Dotoo {
namespace GUI {


/*!
 * \brief   The TaskView class is the presentation of a task model.
 *
 *          Abstract: It displays a changeable checkbox for task's 'isDone' state.
 *          It also presentates the title, comment, due date and responsible person if
 *          'isDone' is false. Else TaskView will only display checkbox and title.
 *
 *          Layout: TaskView uses basically a QGridLayout. Additionally two QHBoxLayouts
 *          are used; one for comment line, one for due date and responsibilty.
 *          The checkbox and the title of the task are added directly to the grid layout.
 *
 *          Colors: TaskView takes an input palette as template and changes only following colors:
 *              - Group: All | Role: Base
 *              - Group: All | Role: AlternateBase
 *
 *          Effects: TaskView currently uses QGraphicsDropShadowEffect for displaying a
 *          simple shadow to widen the 3d-feeling.
 */
class TaskView : public QWidget
{
    Q_OBJECT
public:

    /*!
     * \brief    Contains all possible states of this view.
     */
    typedef enum {
        Normal,     /*!< Normal status. */
        Focussed,   /*!< Selected by user, e.g. */
        Disabled    /*!< Not selectable by user. */
    } State;

private:
    // Indeces of rows:
    static const quint8 RowIdxMain = 0;
    static const quint8 RowIdxComment = 1;
    static const quint8 RowIdxSubInformation = 2;

    // Indeces of columns:
    static const quint8 ClmnIdxCheckBox = 0;
    static const quint8 ClmnIdxTitle = 1;
    static const quint8 ClmnIdxComment = 1;
    static const quint8 ClmnIdxSubInformation = 1;

public:
    TaskView( const QPalette& appPalette, QWidget* parent=nullptr );
    virtual ~TaskView();

    /*!
     * \brief   Takes new model instance and updates presentation.
     *
     * \param   TaskViewModel* model        Pointer to new viewmodel instance.
     */
    void setModel( TaskViewModel* model );

    /*!
     * \brief   Delivers the view's model.
     */
    TaskViewModel* model() const { return m_model; }

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

    bool isDone() const { return m_checkBox->state(); }

signals:
    /*!
     * \brief   This signal is emitted when the 'isDone' state of the task was changed.
     *
     * \param   boool isDone        New state of 'isDone' attribute.
     */
    void isDoneToggled( bool isDone );

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

    /*!
     * \brief   Sets the visible state of
     *              - comment
     *              - due date (icon & text)
     *              - responsible person (icon & text)
     *
     * \param   bool visible        Will be forwarded to setVisible of sub information
     *                              widgets.
     */
    void setSubInfoVisible( bool visible );

    /*!
     * \brief   Adapts the widget's look to the new 'isDone'-state.
     *
     * \param   bool isDone         Indicates whether task is done or not.
     */
    void changeIsDonePresentation( bool isDone );

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

    /*!
     * \brief   Handles the state change of taksview'w checkbox.
     *
     * \param   bool state          New state of checkbox.
     */
    void onCheckBoxStateChange( bool state );


private:
    TaskViewModel* m_model;                     /*!< Reference to model that contains presentated data. */
    State m_state;                              /*!< View's current state. */
    bool m_highlighted;                         /*!< Stores highlighted (by mouse over event e.g.) state. */

    // Sub-widgets:
    CustomGUI::CustomCheckBox* m_checkBox;      /*!< Displays 'isDone' attribute. Interactive. */
    QLabel* m_title;                            /*!< Displays model's 'title' attribute as text. */
    QLabel* m_comment;                          /*!< Displays model's 'comment' attribute as text. */
    QSvgWidget* m_calendarIcon;                 /*!< Calendar icon for that leads 'due date' presentation. */
    QLabel* m_dueDate;                          /*!< Displays model's 'due date' attribute. */

    QSvgWidget* m_personIcon;                   /*!< Person icon that leads model's 'responsible person' presentation. */
    QLabel* m_responsible;                      /*!< Displays model's 'responsible person' attribute. */

    // Style:
    QFont m_titleFont;                          /*!< Font for title. The biggest font. */
    QFont m_commentFont;                        /*!< Font for the comment text. Smaller than title. */
    QFont m_subInfoFont;                        /*!< Font for sub-information. Smallest presentation. */
};


} // namespace GUI;
} // namespace Dotoo;

#endif // TASKVIEW_H
