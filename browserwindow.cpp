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
