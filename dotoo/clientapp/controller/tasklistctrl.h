#ifndef TASKLISTCTRL_H
#define TASKLISTCTRL_H

#include <QObject>


namespace Dotoo {
namespace GUI {


/*!
 * \brief   The TaskListCtrl class is the controller of the 'TaskListView'.
 */
class TaskListCtrl : public QObject
{
    Q_OBJECT
public:
    explicit TaskListCtrl(QObject *parent = 0);

signals:

public slots:
};


} // namespace GUI
} // namespace Dotoo

#endif // TASKLISTCTRL_H
