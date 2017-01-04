#include "settingsctrl.h"

#include "utilz/languagesetting.h"
#include "settingsview.h"


namespace Dotoo {
namespace GUI {


SettingsCtrl::SettingsCtrl( SettingsView* settingsView,
                            LanguageSetting* languageModel,
                            QObject* parent )
    : QObject( parent ),
      m_view( settingsView ),
      m_languageModel( languageModel )
{
    if ( m_view )
    {
        connect( m_view, &SettingsView::clickedApply,
                 this, &SettingsCtrl::onClickedApply );
    }
}


/* Private slots: */

void SettingsCtrl::onClickedApply()
{
    if ( m_view )
    {
        if ( m_languageModel )
        {
            m_languageModel->loadLanguage( m_view->selectedLanguageLocale() );
        }
    }
}


} // namespace Dotoo
} // namespace GUI

