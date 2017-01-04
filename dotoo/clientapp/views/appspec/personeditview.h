#ifndef PERSONEDITVIEW_H
#define PERSONEDITVIEW_H

#include <QWidget>

#include "personviewmodel.h"


class QLineEdit;
class QDateEdit;
class QSvgWidget;
class QLabel;
class QPushButton;
class QComboBox;


namespace Dotoo {
namespace GUI {


class PersonEditView : public QWidget
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
    PersonEditView( const QPalette& appPalette, QWidget* parent=nullptr );
    ~PersonEditView();

public:
    /*!
     * \brief   Takes new model instance and updates presentation.
     *
     * \param   TaskViewModel* model        Pointer to new viewmodel instance.
     */
    void setModel( PersonViewModel* model );

    /*!
     * \brief   Delivers the view's model.
     */
    PersonViewModel* model() const { return m_model; }

    QString name() const;
    QString forename() const;
    QString comment() const;

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


private:
    PersonViewModel* m_model;           /*!< Reference to model that contains presentated data. */

    // Sub-widgets:
    QSvgWidget* m_personIcon;

    QLabel* m_lblForename;              /*!< Describes the forename edit for the user. */
    QLineEdit* m_forenameEdit;          /*!< Displays model's 'title' attribute in a line edit. User can change title by using this line edit. */

    QLabel* m_lblName;                  /*!< Describes the name edit for the user. */
    QLineEdit* m_nameEdit;              /*!< Displays model's 'title' attribute in a line edit. User can change title by using this line edit. */

    QLabel* m_lblComment;               /*!< Describes the comment edit for the user. */
    QLineEdit* m_commentEdit;           /*!< User input for comment attribute. */

    QPushButton* m_btnAbort;            /*!< User input button for aborting editing person. */
    QPushButton* m_btnApply;            /*!< User input button for apply changes on person. */

    // Style:
    QFont m_nameFont;                   /*!< Font for name and forename. */
    QFont m_commentFont;                /*!< Font for the comment text. Smaller than nameFont. */
};


} // namespace GUI;
} // namespace Dotoo;

#endif // PERSONEDITVIEW_H
