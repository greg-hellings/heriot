#include "src/settings/heriotsettings.h"
#include "src/ui/heriot/tabs/maintabwidget.h"

HeriotSettings::HeriotSettings(QObject *parent) :
    QSettings(QSettings::IniFormat, QSettings::UserScope, "Heriot Browser Project", "Heriot Browser", parent)
{
}

void HeriotSettings::saveTabs(MainTabWidget *tabs)
{
    this->setValue("opentabs", tabs->getTabSettings()->toString());
}

static HeriotSettings* instance = 0;

HeriotSettings* HeriotSettings::instance()
{
    if (::instance == NULL)
        ::instance = new HeriotSettings();

    return ::instance;
}
