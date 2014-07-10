#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include "src/ui/tabs/sidetabs.h"
#include "src/settings/heriotsettings.h"

class HeriotWebView;
class QWebInspector;
class CookieJar;
class TabSettings;
class TabSetting;

class MainTabWidget : public SideTabs
{
    Q_OBJECT
public:
    explicit MainTabWidget(QWidget *parent = 0);
    void setTabAddress(const QString& location);

    void navigatePaneBack();
    void navigatePaneForward();
    HeriotWebView* getNewWebView(QWidget* parent = 0);
    TabSettings* getTabSettings();
    void restoreTabSettings(TabSettings* tabSettings);

signals:
    void tabAddressUpdated(const QString& address);
    void tabTitleUpdated(const QString& title);
    void iconChanged(const QString& address);

public slots:
    void urlChanged(const QUrl& url);
    void titleChanged(const QString& title);
    void iconChanged();
    void openNewTab(HeriotWebView *child, HeriotWebView* parent);
    void tabChanged(OpenTab* newTab, OpenTab* oldTab);
    void tabClosing(int remainingTabs);

private:
    HeriotWebView* currentWebView();
    CookieJar* cookieJar;

    void restoreTabSettings(const TabSetting& setting, const OpenTab* parent = 0);
protected:
    void configureNewTab(OpenTab *newTab);
    OpenTab* getNewOpenTab(QWidget* content, QTreeWidgetItem* parent);
    OpenTab* getNewOpenTab(QWidget* content, QTreeWidget* parent);
};

#endif // MAINTABVIEW_H
