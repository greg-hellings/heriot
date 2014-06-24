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

private:
    void setChildren(const QJsonArray& children);
};

class TabSettings : private QJsonDocument
{
public:
    TabSettings(const QString& document);
    TabSettings();
    ~TabSettings();

    void set(const TabSettingList& list);
    const TabSettingList* get();
    void addSetting(TabSetting* setting);
    QString toString();
private:
    TabSettingList* tabSettingList;
};

#endif // TABSETTINGS_H
