#include "maintabswidget.h"
#include "ui_maintabswidget.h"

#include "opentab.h"
#include "heriotwebview.h"

#include <QItemSelectionModel>
#include <QSizePolicy>
#include <QWebHistory>

MainTabsWidget::MainTabsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTabs()),
    myCurrentWebView(NULL)
{
    this->ui->setupUi(this);

    this->connect(this->ui->tabs, SIGNAL(itemSelectionChanged()), SLOT(tabChanged()));

    this->setCurrentWindow(this->newTab(false));
    this->setTabAddress("http://www.google.com");

    this->ui->tabs->setFocusPolicy(Qt::NoFocus);
}

MainTabsWidget::~MainTabsWidget()
{
    delete ui;
}

void MainTabsWidget::configureNewTab(HeriotWebView* webView)
{
    this->connect(webView, SIGNAL(openNewTab(HeriotWebView*, HeriotWebView*)), SLOT(openNewTab(HeriotWebView*, HeriotWebView*)));

    this->ui->webViews->addWidget(webView);

    // Some default settings to enable - doing it here, rather than in global in case we
    // want to allow different options per-tab or per-view in the future
    QWebSettings* settings = webView->page()->settings();
    settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    settings->setAttribute(QWebSettings::PluginsEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    settings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    settings->setAttribute(QWebSettings::LocalStorageEnabled, true);
}

HeriotWebView* MainTabsWidget::newTab(bool childOfCurrent, bool displayNow)
{
    HeriotWebView* webView = new HeriotWebView(this);
    OpenTab *tab;
    if (!childOfCurrent) {
        tab = new OpenTab(this->ui->tabs, QString("Blank"), webView);
    } else {
        tab = new OpenTab(this->myOpenTab, QString("Blank"), webView);
        this->myOpenTab->setExpanded(true);
    }
    this->configureNewTab(webView);

    if (displayNow) {
        this->setCurrentWindow(webView);
        // Auto-select tab on creation
        this->ui->tabs->clearSelection();
        tab->setSelected(true);
    }

    return webView;
}

void MainTabsWidget::setTabAddress(const QString& place)
{
    QUrl url(place);
    if (url.scheme() == "") {
        url.setScheme("http");
    }
    this->myCurrentWebView->setUrl(url);
}

void MainTabsWidget::setCurrentWindow(HeriotWebView *newCurrentWindow)
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
    this->myCurrentWebView = newCurrentWindow;

    this->ui->webViews->setCurrentWidget(this->myCurrentWebView);

    emit tabAddressUpdated(this->myCurrentWebView->url().toString());
    emit tabTitleUpdated(this->myCurrentWebView->title());
    emit iconChanged(this->myCurrentWebView->url().toString());
}

void MainTabsWidget::navigatePaneBack()
{
    this->myCurrentWebView->page()->history()->back();
}

void MainTabsWidget::navigatePaneForward()
{
    this->myCurrentWebView->page()->history()->forward();
}

void MainTabsWidget::urlChanged(const QUrl &url)
{
    emit tabAddressUpdated(url.toString());
}

void MainTabsWidget::titleChanged(const QString &title)
{
    emit tabTitleUpdated(title);
}

void MainTabsWidget::tabChanged()
{
    QList<QTreeWidgetItem*> tabs = this->ui->tabs->selectedItems();
    // I don't yet know how to grok multiple tab selection and we'll deal with a default
    // selection at a later time, if deselection is possible
    if (tabs.count() == 1) {
        OpenTab* tab = dynamic_cast<OpenTab*>(tabs.at(0));
        this->setCurrentWindow(tab->webView());
        this->myOpenTab = tab;
    }
}

void MainTabsWidget::iconChanged()
{
    emit iconChanged(this->myCurrentWebView->url().toString());
}

void MainTabsWidget::openNewTab(HeriotWebView *child, HeriotWebView* parent)
{
    OpenTab* parentTab = this->findTabByView(parent);
    OpenTab* tab = new OpenTab(parentTab, child->title(), child);
    this->configureNewTab(child);
    parentTab->setExpanded(true);
}

OpenTab* MainTabsWidget::findTabByView(HeriotWebView *view)
{
    QTreeWidgetItem* item = this->ui->tabs->invisibleRootItem();
    return this->findTabByViewRecursion(item, view);
}

OpenTab* MainTabsWidget::findTabByViewRecursion(QTreeWidgetItem* item, HeriotWebView* view)
{
    bool found = false;
    for (int i = 0; i < item->childCount() && !found; ++i) {
        OpenTab* tab = dynamic_cast<OpenTab*>(item->child(i));
        if (tab->webView() == view) {
            return tab;
        }
        tab = this->findTabByViewRecursion(tab, view);
        if (tab != NULL) {
            return tab;
        }
    }

    return NULL;
}
