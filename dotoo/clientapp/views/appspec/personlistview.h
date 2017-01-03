#ifndef PERSONLISTVIEW_H
#define PERSONLISTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsBlurEffect>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>


namespace Dotoo {
namespace GUI {


class PersonListViewModel;
class PersonView;


class PersonListView : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief   Ctor of PersonListView class.
     *
     * \param   const QString headlineText      Init. headline.
     *
     * \param   const QPalette& appPalette      App's color palette. Use this for
     *                                          maintain a consistent color scheme.
     *
     * \param   QWidget* parent                 Parent of new PersonListView object.
     */
    PersonListView( const QString headlineText,
                  const QPalette& appPalette,
                  QWidget* parent=nullptr );

    /*!
     * \brief   Dtor of PersonListViewClass.
     */
    virtual ~PersonListView();


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
     * \param   PersonListViewModel* model        Pointer to new viewmodel instance.
     */
    void setModel( PersonListViewModel* model );

    /*!
     * \brief   Delivers the view's model.
     */
    PersonListViewModel* model() const { return m_model; }

    /*!
     * \brief   Delivers the currently selected task (its view).
     *
     * \return  PersonView*                       View of curently selected task.
     *                                          May be a null pointer.
     */
    PersonView* selectedTask() const { return m_selectedTask; }

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

    /* Filter information: */
    QString filterSearchString() { return m_leFilterSearchString->text(); }


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
     * \param   PersonView* task      The double clicked task.
     */
    void doubleClickedTask( PersonView* task );

    /*!
     * \brief   Emitted when someone changed current task selection.
     */
    void selectionChanged( PersonView* newSelection );

    /*!
     * \brief   Toggled when isDone state of a task was changed by an user.
     *
     * \param   PersonView* task      Impacted PersonView.
     *
     * \param   bool isDone         New isDone state.
     */
    void isDoneToggled( PersonView* task, bool isDone );

    void filterChanged();

public slots:


private:
    /*!
     * \brief   Does the work, that has to be done when task selection changes:
     *          - Set state of currently selected PersonView to normal
     *          - Set member to new pointer
     *          - Set state of new selected PersonView to focussed.
     *
     * \param   PersonView* newSelection          Pointer to new selected PersonView.
     */
    void changeTaskSelection( PersonView* newSelection );

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
    PersonListViewModel* m_model;                 /*!< Reference to data model. */

    // Style:
    QPalette m_defaultPalette;                  /*!< Default palette of whole application. Used to maintain a consistent look. */
    QGraphicsBlurEffect* m_looseFocusEffect;    /*!< Used to show task list as unfocussed. */

    // Widgets & Layouts:
    QLabel* m_headline;                         /*!< Displays the headline. */
    QVBoxLayout* m_listLayout;                  /*!< Contains the PersonView widgets. Surrounded by a scroll area. */

    // Widgets for filter list:
    QLineEdit* m_leFilterSearchString;

    // View specific:
    QList<PersonView*> m_PersonViews;               /*!< All task view instances, that are currently shown by this view. Each item is instantiated by this class. */
    PersonView* m_selectedTask;                   /*!< Holds currently selected task. */
};


} // namespace GUI
} // namespace Dotoo

#endif // PERSONLISTVIEW_H
