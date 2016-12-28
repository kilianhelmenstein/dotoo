#ifndef TASKEDITCTRL_H
#define TASKEDITCTRL_H

#include <QObject>


namespace Dotoo {
namespace GUI {


class TaskEditView;
class TaskListViewModel;
class TaskViewModel;


class TaskEditCtrl : public QObject
{
    Q_OBJECT
public:
    typedef enum {
        Change,         /*!< Choose this mode, if controller only shall try to change edited task. */
        Create          /*!< Choose this mode, if controller shall create the edited task. */
    } Mode;

public:
    explicit TaskEditCtrl( Mode mode,
                           TaskEditView* view,
                           TaskListViewModel* listModel,
                           QObject* parent=nullptr );

public:
    Mode mode() const { return m_mode; }

signals:
    /*!
     * \brief   Will be emitted when user finishe editing of task.
     */
    void userFinished();

private slots:
    void onClickedAbort();
    void onClickedApply();

private:
    static bool WriteModel( const TaskEditView& view,
                            TaskViewModel* model );

private:
    const Mode m_mode;
    TaskEditView* m_view;
    TaskListViewModel* m_listModel;
};


} // namespace GUI
} // nameespace Dotoo

#endif // TASKEDITCTRL_H
