#ifndef TASKEDITVIEW_H
#define TASKEDITVIEW_H

#include <QWidget>

#include "taskviewmodel.h"


class QLineEdit;
class QDateEdit;
class QSvgWidget;
class QLabel;
class QPushButton;
class QComboBox;


namespace Dotoo {
namespace GUI {


class PersonListViewModel;



class TaskEditView : public QWidget
{
    Q_OBJECT
private:
    // Indeces of rows:
    static const quint8 RowIdxMain = 0;
    static const quint8 RowIdxComment = 1;
    static const quint8 RowIdxSubInformation = 2;
    static const quint8 RowIdxButtons = 3;

    // Indeces of columns:
    static const quint8 ClmnIdxTitle = 0;
    static const quint8 ClmnIdxComment = 0;
    static const quint8 ClmnIdxSubInformation = 0;
    static const quint8 ClmnIdxButtons = 1;

public:
    TaskEditView( const QPalette& appPalette, QWidget* parent=nullptr );
    ~TaskEditView();

public:
    /*!
     * \brief   Takes new model instance and updates presentation.
     *
     * \param   TaskViewModel* model        Pointer to new viewmodel instance.
     */
    void setModel( TaskViewModel* model );

    /*!
     * \brief   Delivers the view's model.
     */
    TaskViewModel* model() const { return m_model; }

    /*!
     * \brief   Sets the reference to the person list data model.
     */
    void setPersonsModel( PersonListViewModel* personsModel );

    /*!
     * \brief   Delivers the reference to the person list data model.
     */
    PersonListViewModel* personsModel() const { return m_personsModel; }

    /* Getters: */
    QString title() const;
    QString comment() const;
    QDate dueDate() const;
    UniqueId responsible() const;
    UniqueId creator() const;

public slots:
    /*!
     * \brief   Updates all displayed texts (they may depend on selected language).
     */
    void updateDisplayedTexts();

signals:
    /*!
     * \brief   Emitted when 'abort'-button was released.
     */
    void clickedAbort();

    /*!
     * \brief   Emitted when 'apply'-button was released.
     */
    void clickedApply();


private slots:

    /*!
     * \brief   Overrides changeEvent of QWidget.
     *          Currently only updating displayed texts on QEvent::LanguageChange event.
     */
    void changeEvent( QEvent* event );

    /*!
     * \brief   Handles changes of model's data.
     *
     * \note    See 'setMode()'.
     */
    void onModelChange();

    /*!
     * \brief   Handles the deletion of view's model.
     */
    void onModelDeletion();

    /*!
     * \brief   Handles changes of model's data.
     *
     * \note    See 'setMode()'.
     */
    void onPersonsModelChange();

    /*!
     * \brief   Handles the deletion of view's model.
     */
    void onPersonsModelDeletion();

private:
    TaskViewModel* m_model;                     /*!< Reference to model that contains presentated data. */
    PersonListViewModel* m_personsModel;        /*!< Ref. to person list data model. */

    // Sub-widgets:
    QLabel* m_lblTitle;
    QLineEdit* m_titleEdit;                     /*!< Displays model's 'title' attribute in a line edit. User can change title by using this line edit. */

    QLabel* m_lblComment;
    QLineEdit* m_commentEdit;

    QSvgWidget* m_calendarIcon;
    QDateEdit* m_dueDateEdit;                   /*!< Date picker for due date selection. */

    QSvgWidget* m_personIcon;
    QComboBox* m_responsible;

    QPushButton* m_btnAbort;
    QPushButton* m_btnApply;

    // Style:
    QFont m_titleFont;                          /*!< Font for title. The biggest font. */
    QFont m_commentFont;                        /*!< Font for the comment text. Smaller than title. */
    QFont m_subInfoFont;                        /*!< Font for sub-information. Smallest presentation. */
};


} // namespace GUI;
} // namespace Dotoo;

#endif // TASKEDITVIEW_H
