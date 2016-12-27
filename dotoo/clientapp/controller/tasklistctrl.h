#ifndef TASKLISTCTRL_H
#define TASKLISTCTRL_H

#include <QObject>


namespace Dotoo {
namespace GUI {


class TaskListView;
class TaskListViewModel;



/*!
 * \brief   The TaskListCtrl class is the controller of the 'TaskListView'.
 */
class TaskListCtrl : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief   Constructs a valid and working TaskListCtrl instance.
     *          Takes 'view' as the view, that is controlled by instantiated controller.
     *
     * \param   TaskListView* view      View for this controller.
     *
     * \param   QObject* parent         Parent of this object.
     */
    TaskListCtrl( TaskListViewModel* model,
                  TaskListView* view,
                  QObject* parent=nullptr );

signals:

public slots:

private slots:
    void onClickedUpdate();
    void onClickedAdd();
    void onClickedChange();
    void onClickedDelete();

private:
    TaskListViewModel* m_model;     /*!< Stored reference to my model. */
    TaskListView* m_view;           /*!< Stored reference to my view. */
};


} // namespace GUI
} // namespace Dotoo

#endif // TASKLISTCTRL_H
