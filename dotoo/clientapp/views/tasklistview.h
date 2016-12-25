#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsBlurEffect>


#include "viewmodels/tasklistviewmodel.h"
#include "views/taskview.h"



namespace Dotoo {
namespace GUI {


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

signals:

public slots:

private slots:
    /*!
     * \brief   Handles changes of model's data.
     *
     * \note    See 'setModel()'.
     */
    void onModelChange();

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
};


} // namespace GUI
} // namespace Dotoo

#endif // TASKLISTVIEW_H
