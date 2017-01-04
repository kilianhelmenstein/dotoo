#include "settingsview.h"

#include <QEvent>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>

#include "utilz/languagesetting.h"
#include "utilz/textviewutilz.h"


namespace Dotoo {
namespace GUI {


SettingsView::SettingsView( const QPalette& appPalette,
                            QWidget* parent )
    : QWidget( parent ),
      m_languageModel( nullptr ),
      m_lblHeadline( nullptr ),
      m_lblLanguage( nullptr ),
      m_cobLanguageSel( nullptr ),
      m_btnAbort( nullptr ),
      m_btnApply( nullptr )
{
    /****************************************************************/
    /*********                Widget's Layout:                *******/
    /****************************************************************/
    QFormLayout* languageSettingLayout = new QFormLayout();
    QGroupBox* languageSettingGroup = new QGroupBox();
    languageSettingGroup->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    languageSettingGroup->setLayout( languageSettingLayout );

    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    QVBoxLayout* baseLayout = new QVBoxLayout();
    baseLayout->setSizeConstraint( QLayout::SetMinAndMaxSize );
    setLayout( baseLayout );


    /****************************************************************/
    /*********                Widget's Style:                 *******/
    /****************************************************************/
    // Init widget color system:
    setPalette(appPalette);

    // Init fonts:
    m_headlineFont.setPointSize(30);
    m_headlineFont.setStyleHint(QFont::SansSerif);
    m_headlineFont.setWeight(30);

    m_settingsFont.setPointSize(12);
    m_settingsFont.setWeight(50);


    /****************************************************************/
    /*********             Widget's sub-widgets:              *******/
    /****************************************************************/
    m_lblHeadline = new QLabel();
    m_lblHeadline->setFont( m_headlineFont );
    m_lblHeadline->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Maximum );

    // Language setting:
    m_lblLanguage = new QLabel();
    m_lblLanguage->setFont( m_settingsFont );
    m_cobLanguageSel = new QComboBox();
    m_cobLanguageSel->setMaximumWidth( 150 );

    m_btnAbort = new QPushButton();
    connect( m_btnAbort, &QPushButton::clicked,
             this, &SettingsView::onLanguageModelChange );  // Will update view to actual settings
    connect( m_btnAbort, &QPushButton::clicked,
             this, &SettingsView::clickedAbort );

    m_btnApply = new QPushButton();
    connect( m_btnApply, &QPushButton::clicked,
             this, &SettingsView::clickedApply );


    /****************************************************************/
    /*********               Add sub widgets:                 *******/
    /****************************************************************/
    baseLayout->addWidget( m_lblHeadline );

    baseLayout->addWidget( languageSettingGroup );
    languageSettingLayout->addRow( m_lblLanguage, m_cobLanguageSel );

    buttonsLayout->addWidget( m_btnAbort, 1 );
    buttonsLayout->addWidget( m_btnApply, 2 );
    baseLayout->addLayout( buttonsLayout );


    /****************************************************************/
    /*********             Initial Presenation:               *******/
    /****************************************************************/
    setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Maximum );
    setBackgroundRole( QPalette::Background );
    setAutoFillBackground( true );
    updateDisplayedTexts();
}


SettingsView::~SettingsView()
{
}


/* Public methods: */

void SettingsView::setLanguageModel( LanguageSetting* languageModel )
{
    if ( m_languageModel != languageModel )
    {
        if ( m_languageModel )
        {
            disconnect( m_languageModel, 0, this, 0 );
        }

        m_languageModel = languageModel;

        if ( m_languageModel )
        {
            connect( m_languageModel, &LanguageSetting::languageChanged,
                     this, &SettingsView::onLanguageModelChange );
            connect( m_languageModel, &LanguageSetting::destroyed,
                     this, &SettingsView::onLanguageModelDeletion );
            onLanguageModelChange();
        }
    }
}


QString SettingsView::selectedLanguageLocale() const
{
    return m_cobLanguageSel->currentData().toString();
}


/* Public slots: */

void SettingsView::updateDisplayedTexts()
{
    TextViewUtilz::SetTextToLabel( m_lblHeadline, tr("Settings") );
    TextViewUtilz::SetTextToLabel( m_lblLanguage, tr("Language") );

    m_btnAbort->setText( tr("Abort") );
    m_btnApply->setText( tr("Apply") );
}


/* Private slots: */

void SettingsView::changeEvent( QEvent* event )
{
    if ( event->type() == QEvent::LanguageChange )
    {
        updateDisplayedTexts();
    }

    QWidget::changeEvent( event );
}


void SettingsView::onLanguageModelChange()
{
    m_cobLanguageSel->setMaxCount(0);

    QList<LanguageSetting::LanguageInformation> allLang = m_languageModel->availableLanguages();
    m_cobLanguageSel->setMaxCount( allLang.size() );
    foreach ( LanguageSetting::LanguageInformation langInfo, allLang )
    {
        m_cobLanguageSel->addItem( langInfo.langName, QVariant(langInfo.locale) );
    }
}


void SettingsView::onLanguageModelDeletion()
{
    m_languageModel = nullptr;
}


} // namespace GUI
} // namespace Doto
