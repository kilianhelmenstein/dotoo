#ifndef PERSONLISTCTRL_H
#define PERSONLISTCTRL_H

#include <QObject>

#include "personeditctrl.h"


namespace Dotoo {
namespace GUI {

class PersonView;
class PersonListView;
class PersonListViewModel;



/*!
 * \brief   The PersonListCtrl class is the controller of the 'PersonListView'.
 */
class PersonListCtrl : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief   Constructs a valid and working PersonListCtrl instance.
     *          Takes 'view' as the view, that is controlled by instantiated controller.
     *
     * \param   PersonListView* view      View for this controller.
     *
     * \param   QObject* parent         Parent of this object.
     */
    PersonListCtrl( PersonListViewModel* model,
                    PersonListView* view,
                    QObject* parent=nullptr );

signals:

public slots:

private slots:
    /*!
     * \brief   Forces reload of server data.
     */
    void onClickedUpdate();

    /*!
     * \brief   Creates a new view for creating a new Person.
     */
    void onClickedAdd();

    /*!
     * \brief   Creates a new view for editing the clicked Person.
     */
    void onClickedChange();

    /*!
     * \brief   Deletes the current selected Person.
     */
    void onClickedDelete();

    /*!
     * \brief   Creates a new view for editing the clicked Person.
     */
    void onDoubleClickedPerson( PersonView* view );

    /*!
     * \brief   Applies the new filter setting.
     */
    void onFilterChanged();

private:
    /*!
     * \brief   Creates edit view for a Person, a dummy model (that is used as data holder)
     *          and the right controller for the edit view.
     *
     * \param   PersonEditCtrl::Mode modeSelection    Mode selection for behavior of controller: Create a new Person or change a existing one.
     *
     * \return
     */
    PersonEditView* createEditView( PersonEditCtrl::Mode modeSelection,
                                    PersonViewModel* usedModel ) const;

private:
    PersonListViewModel* m_model;     /*!< Stored reference to my model. */
    PersonListView* m_view;           /*!< Stored reference to my view. */
};


} // namespace GUI
} // namespace Dotoo

#endif // PERSONLISTCTRL_H
