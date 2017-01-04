#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>

class QLabel;
class QPushButton;
class QComboBox;

class LanguageSetting;


namespace Dotoo {
namespace GUI {


class SettingsView : public QWidget
{
    Q_OBJECT
public:
    SettingsView( const QPalette& appPalette,
                  QWidget* parent=nullptr );
    ~SettingsView();


    /*!
     * \brief   Delivers view's model for language data.
     */
    LanguageSetting* languageModel() const { return m_languageModel; }

    /*!

     * \brief   Sets the view's model for language data.
     */
    void setLanguageModel( LanguageSetting* languageModel );


    /*!
     * \brief   Delivers the current selected language locale string.
     */
    QString selectedLanguageLocale() const;


public slots:

    /*!
     * \brief   Updates all displayed texts (they may depend on selected language).
     */
    void updateDisplayedTexts();


signals:

    /*!
     * \brief   Emitted when user pressed 'abort' button.
     */
    void clickedAbort();

    /*!
     * \brief   Emitted when user pressed 'apply' button.
     */
    void clickedApply();


private slots:

    /*!
     * \brief   Overrides changeEvent of QWidget.
     *          Currently only updating displayed texts on QEvent::LanguageChange event.
     */
    void changeEvent( QEvent* event );

    /*!
     * \brief   Handles changes of language model.
     */
    void onLanguageModelChange();

    /*!
     * \brief   Handles deletion of language model.
     */
    void onLanguageModelDeletion();

private:
    LanguageSetting* m_languageModel;       /*!< Ref. to language data model. */

    // Sub-Widgets:
    QLabel* m_lblHeadline;                  /*!< Displays headline text. */

    QLabel* m_lblLanguage;                  /*!< Describes m_cobLanguageSel. */
    QComboBox* m_cobLanguageSel;            /*!< User input for language selection. */

    QPushButton* m_btnAbort;                /*!< Button for aborting. */
    QPushButton* m_btnApply;                /*!< Button for applying made changes. */

    QFont m_headlineFont;                   /*!< Font for headline. */
    QFont m_settingsFont;                   /*!< Font for anything else. */
};


} // namespace GUI
} // namespace Doto

#endif // SETTINGSVIEW_H
