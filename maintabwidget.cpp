#include "maintabwidget.h"

#include "heriotwebview.h"
#include "opentab.h"

MainTabWidget::MainTabWidget(QWidget *parent) :
    SideTabs(parent)
{
    this->setTabAddress("http://www.google.com");
}

void MainTabWidget::configureNewTab(OpenTab *newTab)
{
    SideTabs::configureNewTab(newTab);
    HeriotWebView* webView = dynamic_cast<HeriotWebView*>(newTab->widget());

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
    return dynamic_cast<HeriotWebView*>(this->currentTab()->widget());
}

void MainTabWidget::setCurrentWindow()
{
    if (this->myCurrentWebView != NULL) {
        this->disconnect(this->myCurrentWebView, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
        this->disconnect(this->myCurrentWebView, SIGNAL(titleChanged(QString)), this, SLOT(titleChanged(QString)));
        this->disconnect(this->myCurrentWebView, SIGNAL(iconChanged()), this, SLOT(iconChanged()));
        this->disconnect(this->myCurrentWebView, SIGNAL(urlChanged(QUrl)), this, SLOT(iconChanged()));
    }

    this->connect(newCurrentWindow, SIGNAL(urlChanged(QUrl)), SLOT(urlChanged(QUrl)));
    this->connect(newCurrentWindow, SIGNAL(titleChanged(QString)), SLOT(titleChanged(QString)));
    this->connect(newCurrentWindow, SIGNAL(iconChanged()), SLOT(iconChanged()));
    this->connect(newCurrentWindow, SIGNAL(urlChanged(QUrl)), SLOT(iconChanged()));
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
    emit iconChanged(this->myCurrentWebView->url().toString());
}

void MainTabWidget::openNewTab(HeriotWebView *child, HeriotWebView* parent)
{
    OpenTab* parentTab = this->findTabByView(parent);
    OpenTab* tab = this->newTab(child, parent, true);
    parentTab->setExpanded(true);
}
