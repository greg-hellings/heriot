#include "maintabwidget.h"

#include <QWebHistory>

#include "src/ui/heriot/web/heriotwebview.h"
#include "src/ui/tabs/opentab.h"
#include "browsertab.h"
#include "src/ui/heriot/web/webviewwrapper.h"
#include "src/web/cookiejar.h"

MainTabWidget::MainTabWidget(QWidget *parent) :
    SideTabs(parent),
    cookieJar(new CookieJar())
{
    OpenTab* first = this->newTab(this->getNewWebView(), false, true);
    this->setTabAddress("http://www.google.com");
    this->connect(this, SIGNAL(tabChanged(OpenTab*,OpenTab*)), SLOT(tabChanged(OpenTab*,OpenTab*)));
    this->connect(this, SIGNAL(closedTab(int)), SLOT(tabClosing(int)));
    this->tabChanged(NULL, first);
}

void MainTabWidget::configureNewTab(OpenTab *newTab)
{
    SideTabs::configureNewTab(newTab);
    BrowserTab* newBrowserTab = dynamic_cast<BrowserTab*>(newTab);
    HeriotWebView* webView = newBrowserTab->webView();

    this->connect(webView, SIGNAL(openNewTab(HeriotWebView*, HeriotWebView*)), SLOT(openNewTab(HeriotWebView*, HeriotWebView*)));
    // Some default settings to enable - doing it here, rather than in global in case we
    // want to allow different options per-tab or per-view in the future
    QWebSettings* settings = webView->page()->settings();
    settings->setAttribute(QWebSettings::PluginsEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    settings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    settings->setAttribute(QWebSettings::LocalStorageEnabled, true);
}

void MainTabWidget::setTabAddress(const QString& place)
{
    QUrl url(place);
    if (url.scheme() == "") {
        url.setScheme("http");
    }
    this->currentWebView()->setUrl(url);
}

HeriotWebView* MainTabWidget::currentWebView()
{
    return (dynamic_cast<BrowserTab*>(this->currentTab()))->webView();
}

void MainTabWidget::tabChanged(OpenTab* oldTab, OpenTab* newTab)
{
    HeriotWebView* webView = NULL;
    if (newTab != NULL)
        webView = (dynamic_cast<BrowserTab*>(newTab))->webView();
    HeriotWebView* current = NULL;
    if (oldTab != NULL)
        current = (dynamic_cast<BrowserTab*>(oldTab))->webView();

    if (current != NULL) {
        this->disconnect(current, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
        this->disconnect(current, SIGNAL(titleChanged(QString)), this, SLOT(titleChanged(QString)));
        this->disconnect(current, SIGNAL(iconChanged()), this, SLOT(iconChanged()));
        this->disconnect(current, SIGNAL(urlChanged(QUrl)), this, SLOT(iconChanged()));
    }

    if (webView != NULL) {
        this->connect(webView, SIGNAL(urlChanged(QUrl)), SLOT(urlChanged(QUrl)));
        this->connect(webView, SIGNAL(titleChanged(QString)), SLOT(titleChanged(QString)));
        this->connect(webView, SIGNAL(iconChanged()), SLOT(iconChanged()));
        this->connect(webView, SIGNAL(urlChanged(QUrl)), SLOT(iconChanged()));

        this->titleChanged(webView->title());
        this->urlChanged(webView->url());
        this->iconChanged();
    }
}

OpenTab* MainTabWidget::getNewOpenTab(QWidget *content, QTreeWidgetItem *parent)
{
    WebViewWrapper* wrapper = new WebViewWrapper();
    wrapper->addWebView(dynamic_cast<HeriotWebView*>(content));
    return new BrowserTab(parent, QString(""), wrapper);
}

OpenTab* MainTabWidget::getNewOpenTab(QWidget *content, QTreeWidget *parent)
{
    WebViewWrapper* wrapper = new WebViewWrapper();
    wrapper->addWebView(dynamic_cast<HeriotWebView*>(content));
    return new BrowserTab(parent, QString(""), wrapper);
}

HeriotWebView* MainTabWidget::getNewWebView(QWidget* parent)
{
    if (parent == 0 || parent == NULL)
        parent = this;
    HeriotWebView* webView = new HeriotWebView(parent);
    webView->page()->networkAccessManager()->setCookieJar(this->cookieJar);
    this->cookieJar->setParent(this);
    return webView;
}

void MainTabWidget::navigatePaneBack()
{
    this->currentWebView()->page()->history()->back();
}

void MainTabWidget::navigatePaneForward()
{
    this->currentWebView()->page()->history()->forward();
}

void MainTabWidget::urlChanged(const QUrl &url)
{
    emit tabAddressUpdated(url.toString());
}

void MainTabWidget::titleChanged(const QString &title)
{
    emit tabTitleUpdated(title);
}

void MainTabWidget::iconChanged()
{
    emit iconChanged(this->currentWebView()->url().toString());
}

void MainTabWidget::openNewTab(HeriotWebView *child, HeriotWebView* parent)
{
    OpenTab* parentTab = this->findTabByWidget(parent);
    this->newTab(child, parent, true);
    parentTab->setExpanded(true);
}

void MainTabWidget::tabClosing(int remainingTabs)
{
    if (remainingTabs == 0)
        this->setCurrentTab(this->newTab(this->getNewWebView()));
}
