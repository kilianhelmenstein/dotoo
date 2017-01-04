#include "languagesetting.h"

#include <QApplication>
#include <QTranslator>
#include <QDir>
#include <QLocale>


bool switchTranslator( QTranslator& translator, const QString& filename )
{
    // remove the old translator
    QApplication::instance()->removeTranslator(&translator);

    // load the new translator
    if( translator.load(filename) )
    {
        QApplication::instance()->installTranslator( &translator );
        return true;    // Success.
    } else
    {
        return false;   // Error.
    }
}


LanguageSetting::LanguageSetting( const QString& languageDirectory,
                                  QObject* parent )
    : QObject( parent ),
      m_translator( new QTranslator(this) ),
      m_langPath( QApplication::applicationDirPath() + "/" + languageDirectory )
{
    scanLanguageFiles();
}


QList<LanguageSetting::LanguageInformation> LanguageSetting::availableLanguages() const
{
    QList<LanguageInformation> result;

    for ( QMap<QString, TranslationFileInfo>::const_iterator translation = m_availableLang.begin() ;
          translation != m_availableLang.end() ;
          ++translation )
    {
        result.append( (*translation).langInfo );
    }

    return result;
}


bool LanguageSetting::loadLanguage( const QString& localeName )
{
    if ( m_currLang == localeName ) return true;

    if ( m_availableLang.contains(localeName) )
    {
        QLocale locale = QLocale( localeName );
        QLocale::setDefault( locale );

        if ( switchTranslator( *m_translator,
                               m_langPath + "/" + m_availableLang.value(localeName).fileName ))
        {
            m_currLang = localeName;
            emit languageChanged();
            return true;
        }
    }

    return false;
}


void LanguageSetting::scanLanguageFiles()
{
    // Format systems language:
    QString defaultLocale = QLocale::system().name();               // get locale string. E.g. "en_EN"
    defaultLocale.truncate( defaultLocale.lastIndexOf(2) );         // gets lang part of locale string

    // Scan language directory:
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList( QStringList("*.qm") );

    m_availableLang.clear();
    for ( int i=0 ; i < fileNames.size() ; ++i )
    {
        // Get locale extracted by filename
        QString locale;
        locale = fileNames[i];                      // --> "TranslationExample_de.qm"
        locale.truncate(locale.lastIndexOf('.'));   // --> "TranslationExample_de"
        locale.remove( 0, locale.indexOf('_')+1 );  // --> "de"

        QString lang = QLocale::languageToString( QLocale(locale).language() );

        TranslationFileInfo translationInfo { locale, lang, fileNames[i] };
        m_availableLang.insert( locale, translationInfo );
    }
}

