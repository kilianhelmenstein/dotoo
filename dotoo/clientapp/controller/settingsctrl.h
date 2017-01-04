#ifndef SETTINGSCTRL_H
#define SETTINGSCTRL_H

#include <QObject>

class LanguageSetting;


namespace Dotoo {
namespace GUI {

class SettingsView;


class SettingsCtrl : public QObject
{
    Q_OBJECT
public:
    explicit SettingsCtrl( SettingsView* settingsView,
                           LanguageSetting* languageModel,
                           QObject* parent=nullptr );

private slots:

    /*!
     * \brief   Handles click on 'apply' button. Will write all models with
     *          current selected data.
     */
    void onClickedApply();

private:
    SettingsView* m_view;
    LanguageSetting* m_languageModel;
};


} // namespace Dotoo
} // namespace GUI

#endif // SETTINGSCTRL_H
