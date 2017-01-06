#ifndef PERSONLISTVIEW_H
#define PERSONLISTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsBlurEffect>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

#include "customiconbutton.h"


namespace Dotoo {
namespace GUI {


class PersonListViewModel;
class PersonView;


class PersonListView : public QWidget
{
    Q_OBJECT
public:
    static const unsigned int ToolboxIconSize = 60; /*!< Size of toolbox icons. */

public:
    /*!
     * \brief   Ctor of PersonListView class.
     *
     * \param   const QPalette& appPalette      App's color palette. Use this for
     *                                          maintain a consistent color scheme.
     *
     * \param   QWidget* parent                 Parent of new PersonListView object.
     */
    PersonListView( const QPalette& appPalette,
                    QWidget* parent=nullptr );

    /*!
     * \brief   Dtor of PersonListViewClass.
     */
    virtual ~PersonListView();

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
     * \brief   Delivers the currently selected Person (its view).
     *
     * \return  PersonView*                       View of curently selected Person.
     *                                          May be a null pointer.
     */
    PersonView* selectedPerson() const { return m_selectedPerson; }

    /*!
     * \brief   Changes the current Person selection.
     *
     * \param   uint index      The index of the next selected Person.
     *
     * \return bool             True if selection is done.
     *                          False if selected index is invalid.
     */
    bool setPersonSelection( int index );

    bool visualFocus() const;

    void setVisualFocus( bool visualFocus );

    /* Filter information: */
    QString filterSearchString() { return m_leFilterSearchString->text(); }


public slots:
    /*!
     * \brief   Updates all displayed texts (they may depend on selected language).
     */
    void updateDisplayedTexts();

signals:
    /*!
     * \brief   Emitted when 'update Person' button was clicked.
     */
    void clickedUpdate();

    /*!
     * \brief   Emitted when 'add Person' button was clicked.
     */
    void clickedAdd();

    /*!
     * \brief   Emitted when 'change Person' button was clicked.
     */
    void clickedChange();

    /*!
     * \brief   Emitted when 'delete Person' button was clicked.
     */
    void clickedDelete();

    /*!
     * \brief   Emitted when a person was clicked double times.
     *
     * \param   PersonView* person      The double clicked person.
     */
    void doubleClickedPerson( PersonView* Person );

    /*!
     * \brief   Emitted when someone changed current Person selection.
     */
    void selectionChanged( PersonView* newSelection );

    /*!
     * \brief   Emitted when a filter setting was changed by user.
     */
    void filterChanged();

private:

    /*!
     * \brief   Overrides changeEvent of QWidget.
     *          Currently only updating displayed texts on QEvent::LanguageChange event.
     */
    void changeEvent( QEvent* event );

    /*!
     * \brief   Does the work, that has to be done when Person selection changes:
     *          - Set state of currently selected PersonView to normal
     *          - Set member to new pointer
     *          - Set state of new selected PersonView to focussed.
     *
     * \param   PersonView* newSelection          Pointer to new selected PersonView.
     */
    void changePersonSelection( PersonView* newSelection );

private slots:
    /*!
     * \brief   Handles changes of model's data.
     *
     * \note    See 'setModel()'.
     */
    void onModelChange();

    /*!
     * \brief   Handles a user click on a Person item.
     */
    void onPersonClicked();

    /*!
     * \brief   Handles a user double click on a Person item.
     */
    void onPersonDoubleClicked();


private:
    // Parameters:
    PersonListViewModel* m_model;                 /*!< Reference to data model. */

    // Style:
    QPalette m_defaultPalette;                  /*!< Default palette of whole application. Used to maintain a consistent look. */
    QGraphicsBlurEffect* m_looseFocusEffect;    /*!< Used to show Person list as unfocussed. */

    // Widgets & Layouts:
    QLabel* m_headline;                         /*!< Displays the headline. */
    QGridLayout* m_listLayout;                  /*!< Contains the PersonView widgets. Surrounded by a scroll area. */

    // Widgets for filter list:
    QLabel* m_lblSearchString;
    QLineEdit* m_leFilterSearchString;

    CustomGUI::CustomIconButton* m_toolUpdate;
    CustomGUI::CustomIconButton* m_toolAdd;
    CustomGUI::CustomIconButton* m_toolChange;
    CustomGUI::CustomIconButton* m_toolDelete;

    // View specific:
    QList<PersonView*> m_personViews;               /*!< All Person view instances, that are currently shown by this view. Each item is instantiated by this class. */
    PersonView* m_selectedPerson;                   /*!< Holds currently selected Person. */
};


} // namespace GUI
} // namespace Dotoo

#endif // PERSONLISTVIEW_H
