#ifndef PERSONEDITCTRL_H
#define PERSONEDITCTRL_H

#include <QObject>


namespace Dotoo {
namespace GUI {


class PersonEditView;
class PersonListViewModel;
class PersonViewModel;


class PersonEditCtrl : public QObject
{
    Q_OBJECT
public:
    typedef enum {
        Change,         /*!< Choose this mode, if controller only shall try to change edited person. */
        Create          /*!< Choose this mode, if controller shall create the edited person. */
    } Mode;

public:
    explicit PersonEditCtrl( Mode mode,
                             PersonEditView* view,
                             PersonListViewModel* listModel,
                             QObject* parent=nullptr );

public:
    Mode mode() const { return m_mode; }

signals:
    /*!
     * \brief   Will be emitted when user finishe editing of person.
     */
    void userFinished();

private slots:
    void onClickedAbort();
    void onClickedApply();

private:
    static bool WriteModel( const PersonEditView& view,
                            PersonViewModel* model );

private:
    const Mode m_mode;
    PersonEditView* m_view;
    PersonListViewModel* m_listModel;
};


} // namespace GUI
} // nameespace Dotoo

#endif // PERSONEDITCTRL_H
