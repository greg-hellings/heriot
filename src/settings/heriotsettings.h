#ifndef HERIOTSETTINGS_H
#define HERIOTSETTINGS_H

#include <QSettings>
#include <QMap>
#include <QList>
#include "tabsettings.h"

class MainTabWidget;

class HeriotSettings : public QSettings
{
    Q_OBJECT
public:
    static HeriotSettings* instance();

    void saveTabs(MainTabWidget* tabs);
signals:

public slots:

private:
    explicit HeriotSettings(QObject *parent = 0);
};

#endif // HERIOTSETTINGS_H
