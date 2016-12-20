#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QWidget>
#include <QVBoxLayout>

#include "viewmodels/tasklistviewmodel.h"
#include "views/taskview.h"



namespace Dotoo {
namespace GUI {

class TaskListView : public QWidget
{
    Q_OBJECT
public:
    TaskListView( const QPalette& appPalette, QWidget *parent=nullptr );
    virtual ~TaskListView();

    /*!
     * \brief   Takes new model instance and updates presentation.
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
     * \note    See 'setMode()'.
     */
    void onModelChange();

private:
    TaskListViewModel* m_model;

    QList<TaskView*> m_taskViews;

    // Style
    QPalette m_defaultPalette;

    QVBoxLayout* m_listLayout;
};


} // namespace GUI
} // namespace Dotoo

#endif // TASKLISTVIEW_H
