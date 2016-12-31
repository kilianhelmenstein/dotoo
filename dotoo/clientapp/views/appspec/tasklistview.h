#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsBlurEffect>
#include <QLabel>


namespace Dotoo {
namespace GUI {


class TaskListViewModel;
class TaskView;



/*!
 * \brief   The TaskListView class dipslays a cluster of tasks, whereby data is provided
 *          by a 'TaskListViewModel' object (see setModel()).
 *
 *          The view for a task list contains three main sections:
 *          - At head, there is displayed a headline
 *          - In mid section, there is placed a vbox layout that contains the task views. This
 *          section is surrounded by a scroll area.
 *          - At bottom, there is a tool bar with add-, delete- and change-tool.
 *
 *          The view connects to its model and automatically updates when model changed.
 */
class TaskListView : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief   Ctor of TaskListView class.
     *
     * \param   const QString headlineText      Init. headline.
     *
     * \param   const QPalette& appPalette      App's color palette. Use this for
     *                                          maintain a consistent color scheme.
     *
     * \param   QWidget* parent                 Parent of new TaskListView object.
     */
    TaskListView( const QString headlineText,
                  const QPalette& appPalette,
                  QWidget* parent=nullptr );

    /*!
     * \brief   Dtor of TaskListViewClass.
     */
    virtual ~TaskListView();


    /*!
     * \brief   Updates the headline text.
     *
     * \param   const QString& headlineText     New headline.
     */
    void setHeadline( const QString& headlineText );

    /*!
     * \brief   Takes new model instance and updates presentation. Connects this object wiht
     *          'model' to automatically update view when 'model' changes.
     *
     * \param   TaskListViewModel* model        Pointer to new viewmodel instance.
     */
    void setModel( TaskListViewModel* model );

    /*!
     * \brief   Delivers the view's model.
     */
    TaskListViewModel* model() const { return m_model; }

    /*!
     * \brief   Delivers the currently selected task (its view).
     *
     * \return  TaskView*                       View of curently selected task.
     *                                          May be a null pointer.
     */
    TaskView* selectedTask() const { return m_selectedTask; }

    /*!
     * \brief   Changes the current task selection.
     *
     * \param   uint index      The index of the next selected task.
     *
     * \return bool             True if selection is done.
     *                          False if selected index is invalid.
     */
    bool setTaskSelection( int index );

    bool visualFocus() const;

    void setVisualFocus( bool visualFocus );

signals:
    /*!
     * \brief   Emitted when 'update task' button was clicked.
     */
    void clickedUpdate();

    /*!
     * \brief   Emitted when 'add task' button was clicked.
     */
    void clickedAdd();

    /*!
     * \brief   Emitted when 'change task' button was clicked.
     */
    void clickedChange();

    /*!
     * \brief   Emitted when 'delete task' button was clicked.
     */
    void clickedDelete();

    /*!
     * \brief   Emitted when a task was clicked double times.
     *
     * \param   TaskView* task      The double clicked task.
     */
    void doubleClickedTask( TaskView* task );

    /*!
     * \brief   Emitted when someone changed current task selection.
     */
    void selectionChanged( TaskView* newSelection );

    /*!
     * \brief   Toggled when isDone state of a task was changed by an user.
     *
     * \param   TaskView* task      Impacted taskview.
     *
     * \param   bool isDone         New isDone state.
     */
    void isDoneToggled( TaskView* task, bool isDone );

public slots:


private:
    /*!
     * \brief   Does the work, that has to be done when task selection changes:
     *          - Set state of currently selected taskview to normal
     *          - Set member to new pointer
     *          - Set state of new selected taskview to focussed.
     *
     * \param   TaskView* newSelection          Pointer to new selected taskview.
     */
    void changeTaskSelection( TaskView* newSelection );

private slots:
    /*!
     * \brief   Handles changes of model's data.
     *
     * \note    See 'setModel()'.
     */
    void onModelChange();

    /*!
     * \brief   Handles a user click on a task item.
     */
    void onTaskClicked();

    /*!
     * \brief   Handles a user double click on a task item.
     */
    void onTaskDoubleClicked();

    /*!
     * \brief   Handles the toggle of a task's isDone state.
     *
     * \param   bool isDone     New isDone state.
     */
    void onIsDoneTogled( bool isDone );

private:
    // Parameters:
    TaskListViewModel* m_model;                 /*!< Reference to data model. */

    // Style:
    QPalette m_defaultPalette;                  /*!< Default palette of whole application. Used to maintain a consistent look. */
    QGraphicsBlurEffect* m_looseFocusEffect;    /*!< Used to show task list as unfocussed. */

    // Widgets & Layouts:
    QLabel* m_headline;                         /*!< Displays the headline. */
    QVBoxLayout* m_listLayout;                  /*!< Contains the TaskView widgets. Surrounded by a scroll area. */

    // View specific:
    QList<TaskView*> m_taskViews;               /*!< All task view instances, that are currently shown by this view. Each item is instantiated by this class. */
    TaskView* m_selectedTask;                   /*!< Holds currently selected task. */
};


} // namespace GUI
} // namespace Dotoo

#endif // TASKLISTVIEW_H
