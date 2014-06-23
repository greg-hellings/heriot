#ifndef TABSETTINGS_H
#define TABSETTINGS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class TabSetting;

typedef QList<TabSetting*> TabSettingList;

class TabSetting : public QJsonObject
{
public:
    TabSetting();
    TabSetting(const QJsonObject& convert);

    QString url() const;
    void setUrl(const QString& url);
    TabSettingList* children() const;
    void setChildren(const TabSettingList& children);
    void setChildren(const QJsonArray& children);
};

class TabSettings : public QJsonDocument
{
public:
    void insert(const TabSettingList& list);
};

#endif // TABSETTINGS_H
