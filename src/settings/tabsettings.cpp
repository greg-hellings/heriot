#include "src/settings/tabsettings.h"

#include <QVariant>
#include <QJsonArray>

const QString urlKey = "url";
const QString childrenKey = "children";

TabSetting::TabSetting()
{
}

TabSetting::TabSetting(const QJsonObject &convert)
{
    this->setUrl(convert.value(urlKey).toString());
    this->setChildren(convert.value(childrenKey).toArray());
}

QString TabSetting::url() const
{
    return this->value(urlKey).toString();
}

void TabSetting::setUrl(const QString &url)
{
    this->insert(urlKey, url);
}

/**
 * @brief TabSetting::children
 * @return Pointer to a TabSettingList of all the children on this item
 *
 * User is responsible to delete the list when they are finished with it, along with its contents
 */
TabSettingList* TabSetting::children() const
{
    TabSettingList* tabSettingList = new TabSettingList();
    QJsonArray tabSettingArray = this->value(childrenKey).toArray();
    for (QJsonArray::iterator it = tabSettingArray.begin(); it != tabSettingArray.end(); ++it) {
        tabSettingList->append(new TabSetting((*it).toObject()));
    }
    return tabSettingList;
}

void TabSetting::setChildren(const QJsonArray &children)
{
    this->insert(childrenKey, children);
}

void TabSetting::setChildren(const TabSettingList &children)
{
    QJsonArray jsonArray;
    for (TabSettingList::const_iterator it = children.begin(); it != children.end(); ++it) {
        jsonArray.append(**it);
    }
    this->insert(childrenKey, jsonArray);
}

/***********************
 * Trollolololol
 ***********************/
TabSettings::TabSettings() :
    tabSettingList(new TabSettingList())
{}

TabSettings::TabSettings(const QString &document) :
    QJsonDocument(QJsonDocument::fromJson(document.toUtf8())),
    tabSettingList(new TabSettingList())
{
    QJsonArray myArray = this->array();
    for (QJsonArray::iterator it = myArray.begin(); it != myArray.end(); ++it) {
        this->tabSettingList->append(new TabSetting((*it).toObject()));
    }
}

TabSettings::~TabSettings()
{
    for (int i = this->tabSettingList->count(); i >= 0; --i) {
        delete this->tabSettingList->takeAt(i);
    }
    delete this->tabSettingList;
}

void TabSettings::set(const TabSettingList &list)
{
    QJsonArray jsonArray;
    for (TabSettingList::const_iterator it = list.begin(); it != list.end(); ++it) {
        jsonArray.append(**it);
    }
    this->setArray(jsonArray);
    this->tabSettingList = new TabSettingList(list);
}

void TabSettings::addSetting(TabSetting *setting)
{
    this->tabSettingList->append(setting);
}

const TabSettingList* TabSettings::get()
{
    return this->tabSettingList;
}

QString TabSettings::toString()
{
    return QString(QJsonDocument::toJson());
}
