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
TabSettings::TabSettings()
{
    this->set(new TabSettingList());
}

TabSettings::TabSettings(const QString &document) :
    QJsonDocument(QJsonDocument::fromJson(document.toUtf8()))
{
}

void TabSettings::set(const TabSettingList* list)
{
    QJsonArray jsonArray;
    for (TabSettingList::const_iterator it = list->begin(); it != list->end(); ++it) {
        jsonArray.append(**it);
    }
    this->setArray(jsonArray);
}

TabSettingList* TabSettings::get()
{
    TabSettingList* list = new TabSettingList();
    QJsonArray array = this->array();
    for (int i = 0; i < array.size(); ++i) {
        list->append(new TabSetting(array.at(i).toObject()));
    }

    return list;
}

QString TabSettings::toString()
{
    return QString(QJsonDocument::toJson(QJsonDocument::Compact));
}
