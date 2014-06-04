#include "maintabswidget.h"
#include "ui_maintabswidget.h"

#include "opentab.h"
#include "heriotwebview.h"

#include <QItemSelectionModel>
#include <QSizePolicy>

MainTabsWidget::MainTabsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTabs()),
    myCurrentWebView(NULL)
{
    this->ui->setupUi(this);

    this->setCurrentWindow(this->newTab(false));
    this->setTabAddress("about:blank");
}

MainTabsWidget::~MainTabsWidget()
{
    delete ui;
}

HeriotWebView* MainTabsWidget::newTab(bool childOfCurrent)
{
    HeriotWebView* webView = new HeriotWebView();
    OpenTab *tab;
    if (!childOfCurrent) {
        tab = new OpenTab(this->ui->tabs, QString("Blank"), webView);
    } else {
        tab = new OpenTab(this->myOpenTab, QString("Blank"), webView);
    }

    this->ui->webViews->addWidget(webView);

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

    this->connect(newCurrentWindow, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
    this->connect(newCurrentWindow, SIGNAL(titleChanged(QString)), this, SLOT(titleChanged(QString)));
    this->myCurrentWebView = newCurrentWindow;

    emit tabAddressUpdated(this->myCurrentWebView->url().toString());
    emit tabTitleUpdated(this->myCurrentWebView->title());
}

void MainTabsWidget::urlChanged(const QUrl &url)
{
    emit tabAddressUpdated(url.toString());
}

void MainTabsWidget::titleChanged(const QString &title)
{
    emit tabTitleUpdated(title);
}
