#ifndef TASKVIEW_H
#define TASKVIEW_H

#include <QWidget>
#include <QFont>

class QLabel;
class QSvgWidget;
class CustomCheckBox;

#include "viewmodels/taskviewmodel.h"



namespace Dotoo {


/*!
 * \brief   The TaskView class is the presentation of a task model.
 *
 *          It displays a changeable checkbox for task's 'isDone' state.
 *          It also presentates the title, comment, due date and responsible person if
 *          'isDone' is false. Else TaskView will only display checkbox and title.
 */
class TaskView : public QWidget
{
    Q_OBJECT
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
    TaskView( QWidget* parent=nullptr );
    virtual ~TaskView();

    /*!
     * \brief   Takes new model instance and updates presentation.
     *
     * \param   TaskViewModel* model        Pointer to new viewmodel instance.
     */
    void setModel( TaskViewModel* model );

private:
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

    void changeIsDonePresentation( bool isDone );

private slots:
    /*!
     * \brief   Handles changes of model's data.
     *
     * \note    See 'setMode()'.
     */
    void onModelChange();

    /*!
     * \brief   Handles the state change of taksview'w checkbox.
     *
     * \param   bool state          New state of checkbox.
     */
    void onCheckBoxStateChange( bool state );

signals:
    /*!
     * \brief   This signal is emitted when the 'isDone' state of the task was changed.
     *
     * \param   boool isDone        New state of 'isDone' attribute.
     */
    void isDoneToggled( bool isDone );

private:
    TaskViewModel* m_model;                     /*!< */

    // Sub-widgets:
    CustomCheckBox* m_checkBox;                 /*!< Displays 'isDone' attribute. Interactive. */
    QLabel* m_title;                            /*!< Displays model's 'title' attribute as text. */
    QLabel* m_comment;                          /*!< Displays model's 'comment' attribute as text. */
    QSvgWidget* m_calendarIcon;                 /*!< Calendar icon for that leads 'due date' presentation. */
    QLabel* m_dueDate;                          /*!< Displays model's 'due date' attribute. */
    QSvgWidget* m_personIcon;                   /*!< Person icon that leads model's 'responsible person' presentation. */
    QLabel* m_responsible;                      /*!< Displays model's 'responsible person' attribute. */

    // Style:
    QFont m_titleFont;
    QFont m_commentFont;
    QFont m_subInfoFont;
};


} // namespace Dotoo;

#endif // TASKVIEW_H
