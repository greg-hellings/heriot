#include "heriotapplication.h"

#include <QWebSettings>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>

HeriotApplication::HeriotApplication(int& argc, char** argv) :
    QApplication(argc, argv),
    defaultIcon(QIcon(":heriot.ico"))
{
    // Delay some tasks for after the window is created
    QTimer::singleShot(0, this, SLOT(postLaunch()));
}

HeriotApplication* HeriotApplication::instance()
{
    return dynamic_cast<HeriotApplication*>(QCoreApplication::instance());
}

QIcon HeriotApplication::icon(const QUrl &url)
{
    QIcon icon = QWebSettings::iconForUrl(url);
    if (!icon.isNull())
        return icon.pixmap(16, 16);
    if (this->defaultIcon.isNull())
        this->defaultIcon = QIcon(QString(":heriot.ico"));
    return this->defaultIcon.pixmap(16, 16);
}

void HeriotApplication::postLaunch()
{
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if (directory.isEmpty())
        directory = QDir::homePath() + QLatin1String("/.") + QCoreApplication::applicationName();
    // Create if it doesn't exist
    QDir dir(directory);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QWebSettings::enablePersistentStorage(directory);
    QWebSettings* settings = QWebSettings::globalSettings();
    settings->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
    settings->setThirdPartyCookiePolicy(QWebSettings::AllowThirdPartyWithExistingCookies);
}
