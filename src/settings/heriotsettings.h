#ifndef HERIOTSETTINGS_H
#define HERIOTSETTINGS_H

#include <QSettings>
#include <QMap>
#include <QList>
#include "tabsettings.h"

class MainTabWidget;
class QUuid;
class BrowserWindow;

class HeriotSettings : public QSettings
{
    Q_OBJECT
public:
    static HeriotSettings* instance();

    void saveTabs(const QUuid& uuid, MainTabWidget* tabs);
    QString getTabs(const QUuid& uuid);

    void saveWindow(const BrowserWindow* window);
    void getWindow(BrowserWindow* window);
signals:

public slots:

private:
    explicit HeriotSettings(QObject *parent = 0);
    void setWindowSetting(const QUuid& uuid, const QString& name, const QString& value = "");
    QVariant getWindowSetting(const QUuid& uuid, const QString& name, const QString& defaultValue = "");

    static const QString tabs;
    static const QString geometry;
    static const QString windows;
};

#endif // HERIOTSETTINGS_H
