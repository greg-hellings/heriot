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
    explicit HeriotSettings(QObject *parent = 0);
    static HeriotSettings* instance() {
        if (s_instance == NULL)
            s_instance = new HeriotSettings();

        return s_instance;
    }
signals:

public slots:

private:
    static HeriotSettings* s_instance;
};

#endif // HERIOTSETTINGS_H
