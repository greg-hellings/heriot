#include "src/settings/heriotsettings.h"
#include "src/ui/heriot/tabs/maintabwidget.h"
#include "src/ui/windows/browser/browserwindow.h"

#include <QUuid>

const QString HeriotSettings::tabs = "tabs";
const QString HeriotSettings::position = "position";
const QString HeriotSettings::size = "size";
const QString HeriotSettings::windows = "windows";

HeriotSettings::HeriotSettings(QObject *parent) :
    QSettings(QSettings::IniFormat, QSettings::UserScope, "Heriot Browser Project", "Heriot Browser", parent)
{
}

void HeriotSettings::saveTabs(const QUuid& uuid, MainTabWidget *tabs)
{
    this->setWindowSetting(uuid, HeriotSettings::tabs, tabs->getTabSettings()->toString());
}

QString HeriotSettings::getTabs(const QUuid& uuid)
{
    return this->getWindowSetting(uuid, HeriotSettings::tabs, "[]").toString();
}

void HeriotSettings::clearTabs()
{
    this->beginGroup(HeriotSettings::windows);
    this->remove("");
    this->endGroup();
}

void HeriotSettings::saveWindow(const BrowserWindow* window)
{
    this->setWindowSetting(window->uuid(), HeriotSettings::position, window->pos());
    this->setWindowSetting(window->uuid(), HeriotSettings::size, window->size());
}

void HeriotSettings::getWindow(BrowserWindow* window) {
    window->move(this->getWindowSetting(window->uuid(), HeriotSettings::position).toPoint());
    window->resize(this->getWindowSetting(window->uuid(), HeriotSettings::size).toSize());
}

QStringList HeriotSettings::getWindows()
{
    this->beginGroup(HeriotSettings::windows);
    QStringList childGroups = this->childGroups();
    this->endGroup();
    return childGroups;
}

void HeriotSettings::setWindowSetting(const QUuid &uuid, const QString &name, const QVariant &value)
{
    this->beginGroup(HeriotSettings::windows);
    this->beginGroup(uuid.toString());
    this->setValue(name, value);
    this->endGroup();
    this->endGroup();
}

QVariant HeriotSettings::getWindowSetting(const QUuid &uuid, const QString &name, const QVariant &defaultValue)
{
    this->beginGroup(HeriotSettings::windows);
    this->beginGroup(uuid.toString());
    QVariant value = this->value(name, defaultValue);
    this->endGroup();
    this->endGroup();

    return value;
}

static HeriotSettings* instance = 0;

HeriotSettings* HeriotSettings::instance()
{
    if (::instance == NULL)
        ::instance = new HeriotSettings();

    return ::instance;
}
