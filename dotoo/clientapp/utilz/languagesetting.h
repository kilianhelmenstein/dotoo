#ifndef LANGUAGESETTING_H
#define LANGUAGESETTING_H


#include <QObject>

class QTranslator;



/*!
 * \brief   The LanguageSetting class makes it easy to get all available translations
 *          and select a new application language.
 *
 *          At application start, the system language will be choosen.
 *
 * \note    Class expects that language file naming works as follows: '<SomeName>_de.qm'.
 *
 * \see     https://wiki.qt.io/How_to_create_a_multi_language_application/de
 */
class LanguageSetting : public QObject
{
    Q_OBJECT
private:
    /*!
     * \brief   Contains all necessary information about a translation file.
     */
    typedef struct {
        QString locale;         /*!< Locale, e.g.'de' */
        QString langName;       /*!< Lang. name, e.g.'Deutsch' */
        QString fileName;       /*!< File name, e.g.'SomeName_de.qm' */
    } TranslationFileInfo;

public:
    /*!
     * \brief   Ctor for LanguageSetting instances.
     *
     * \param   const QString& languageDirectory    Path to language directory relative to app's dir.
     */
    LanguageSetting( const QString& languageDirectory,
                     QObject* parent=nullptr );

    /*!
     * \brief   Sets the absolute path to language file directory.
     */
    void setAbsoluteLangPath( const QString& absLangPath )
    {
        m_langPath = absLangPath;
        scanLanguageFiles();
    }

    /*!
     * \brief   Returns a locale-LangName-map with all currently selectable languages.
     *
     * \return  QMap<QString,QString>           Key: Locale; Value: Language name
     */
    QMap<QString,QString> availableLanguages() const;

private:
    /*!
     * \brief   Creates the language menu dynamically from the content of m_langPath
     */
    void scanLanguageFiles();

    /*!
     * \brief   Loads a language by the given language shortcur (e.g. de, en, …)
     *
     * \param   const QString& lang     Language (locale) to load
     */
    void loadLanguage( const QString& localeName );


private:
    QTranslator* m_translator;  /*!< contains the translations for this application*/

    QMap<QString, TranslationFileInfo> m_availableLang;  /*!< Key=Locale. List of all available translations. */
    QString m_currLang;         /*!< contains the currently loaded language*/
    QString m_langPath;         /*!< Path of language files. This is always fixed to /lang.*/
};

#endif // LANGUAGESETTING_H
