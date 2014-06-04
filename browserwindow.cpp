#include "browserwindow.h"
#include "ui_browserwindow.h"
#include "maintabswidget.h"

#include <QWebView>
#include <QTabWidget>

BrowserWindow::BrowserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrowserWindow)
{
    this->ui->setupUi(this);

    this->mainTabsWidget = this->ui->mainTabsWidget;

    this->connect(this->ui->omniBox, SIGNAL(returnPressed()), SLOT(omniValueEntered()));
    this->connect(this->mainTabsWidget, SIGNAL(tabAddressUpdated(QString)), SLOT(currentTabAddressChanged(QString)));
    this->connect(this->mainTabsWidget, SIGNAL(tabTitleUpdated(QString)), SLOT(currentTabTitleChanged(QString)));

    this->connect(this->ui->actionNew_Tab, SIGNAL(triggered()), SLOT(openNewTab()));
    this->connect(this->ui->actionNew_Child_Tab, SIGNAL(triggered()), SLOT(openNewChildTab()));

    this->connect(this->ui->backButton, SIGNAL(clicked(bool)), SLOT(backNavigation(bool)));
    this->connect(this->ui->forwardButton, SIGNAL(clicked(bool)), SLOT(forwardNavigation(bool)));

    this->connect(this->ui->actionExit, SIGNAL(triggered()), SLOT(quit()));
    this->connect(this->ui->actionClose_Window, SIGNAL(triggered()), SLOT(close()));
    this->connect(this->ui->actionNew_Window, SIGNAL(triggered()), SLOT(newWindow()));

    // This only works in a global setting, but it speeds up browsing
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
}

BrowserWindow::~BrowserWindow()
{
    delete ui;
}

void BrowserWindow::omniValueEntered()
{
    this->mainTabsWidget->setTabAddress(this->ui->omniBox->text());
}

void BrowserWindow::currentTabAddressChanged(const QString &address)
{
    this->ui->omniBox->setText(address);
}

void BrowserWindow::currentTabTitleChanged(const QString &title)
{
    this->setWindowTitle(title);
}

void BrowserWindow::openNewTab()
{
    this->mainTabsWidget->newTab(false);
}

void BrowserWindow::openNewChildTab()
{
    this->mainTabsWidget->newTab(true);
}

void BrowserWindow::backNavigation(bool)
{
    this->mainTabsWidget->navigatePaneBack();
}

void BrowserWindow::forwardNavigation(bool)
{
    this->mainTabsWidget->navigatePaneForward();
}

void BrowserWindow::quit()
{
    QApplication::quit();
}

void BrowserWindow::newWindow()
{
    BrowserWindow* window = new BrowserWindow();
    window->show();
}
