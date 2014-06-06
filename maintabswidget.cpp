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
}

MainTabsWidget::~MainTabsWidget()
{
    delete ui;
}

HeriotWebView* MainTabsWidget::newTab(bool childOfCurrent, bool displayNow)
{
    HeriotWebView* webView = new HeriotWebView();
    OpenTab *tab;
    if (!childOfCurrent) {
        tab = new OpenTab(this->ui->tabs, QString("Blank"), webView);
    } else {
        tab = new OpenTab(this->myOpenTab, QString("Blank"), webView);
    }
    // Auto-select tab on creation
    this->ui->tabs->clearSelection();
    tab->setSelected(true);

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

    if (displayNow) {
        this->setCurrentWindow(webView);
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
    }

    this->connect(newCurrentWindow, SIGNAL(urlChanged(QUrl)), SLOT(urlChanged(QUrl)));
    this->connect(newCurrentWindow, SIGNAL(titleChanged(QString)), SLOT(titleChanged(QString)));
    this->myCurrentWebView = newCurrentWindow;

    this->ui->webViews->setCurrentWidget(this->myCurrentWebView);

    emit tabAddressUpdated(this->myCurrentWebView->url().toString());
    emit tabTitleUpdated(this->myCurrentWebView->title());
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
