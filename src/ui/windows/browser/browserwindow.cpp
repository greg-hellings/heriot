#include "browserwindow.h"
#include "ui_browserwindow.h"
#include "src/ui/heriot/tabs/maintabwidget.h"
#include "src/heriotapplication.h"
#include "src/ui/heriot/web/heriotwebview.h"

#include <QWebEngineView>
#include <QTabWidget>
#include <QKeyEvent>
#include <QDockWidget>
#include <QFileDialog>
#include <QUuid>

BrowserWindow::BrowserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrowserWindow),
    o_uuid(QUuid::createUuid())
{
    this->init();
}

BrowserWindow::BrowserWindow(const QString& uuid, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrowserWindow),
    o_uuid(uuid)
{
    this->init();
    HeriotSettings::instance()->getWindow(this);
    this->mainTabsWidget->restoreTabSettings(new TabSettings(HeriotSettings::instance()->getTabs(this->o_uuid)));
}

BrowserWindow::~BrowserWindow()
{
    delete this->ui;
}

const QUuid BrowserWindow::uuid() const
{
    return this->o_uuid;
}

void BrowserWindow::init()
{
    this->ui->setupUi(this);

    this->mainTabsWidget = this->ui->mainTabsWidget;

    this->connect(this->ui->omniBox, SIGNAL(returnPressed()), SLOT(omniValueEntered()));
    this->connect(this->mainTabsWidget, SIGNAL(tabAddressUpdated(QString)), SLOT(currentTabAddressChanged(QString)));
    this->connect(this->mainTabsWidget, SIGNAL(tabTitleUpdated(QString)), SLOT(currentTabTitleChanged(QString)));
    this->connect(this->mainTabsWidget, SIGNAL(tabAddressUpdated(QString)), SLOT(iconChanged(QString)));
    this->connect(this->mainTabsWidget, SIGNAL(iconChanged(QString)), SLOT(iconChanged(QString)));

    this->connect(this->ui->actionNew_Tab, SIGNAL(triggered()), SLOT(openNewTab()));
    this->connect(this->ui->actionNew_Child_Tab, SIGNAL(triggered()), SLOT(openNewChildTab()));
    this->connect(this->ui->actionExit, SIGNAL(triggered()), SLOT(quit()));
    this->connect(this->ui->actionClose_Window, SIGNAL(triggered()), SLOT(close()));
    this->connect(this->ui->actionNew_Window, SIGNAL(triggered()), SLOT(newWindow()));
    this->connect(this->ui->actionOpen_File, SIGNAL(triggered()), SLOT(onOpenFile()));

    this->connect(this->ui->backButton, SIGNAL(clicked(bool)), SLOT(backNavigation(bool)));
    this->connect(this->ui->forwardButton, SIGNAL(clicked(bool)), SLOT(forwardNavigation(bool)));
    this->connect(this->ui->refreshButton, SIGNAL(clicked(bool)), SLOT(refresh()));

    this->connect(this->ui->actionClose_Tab, SIGNAL(triggered()), SLOT(onCloseCurrentTab()));

    this->setIconSize(QSize(16, 16));
}

void BrowserWindow::closeEvent(QCloseEvent *event)
{
    HeriotSettings* settings = HeriotSettings::instance();
    settings->clearTabs();
    settings->saveTabs(this->uuid(), this->mainTabsWidget);
    settings->saveWindow(this);
    settings->sync();
    QMainWindow::closeEvent(event);
}

void BrowserWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_L:
        if (event->modifiers() & Qt::ControlModifier) {
            this->ui->omniBox->setFocus();
            this->ui->omniBox->selectAll();
        }
        event->ignore();
        break;
    case Qt::Key_F:
        if (event->modifiers() & Qt::ControlModifier) {
//            this->mainTabsWidget->currentWebView()->findText("a");
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void BrowserWindow::onCloseCurrentTab()
{
    this->mainTabsWidget->closeCurrentTab();
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

void BrowserWindow::openNewTab(bool child)
{
    HeriotWebView* webView = this->mainTabsWidget->getNewWebView();
    this->mainTabsWidget->newTab(webView, child);
    this->ui->omniBox->setFocus();
}

void BrowserWindow::openNewChildTab()
{
    this->openNewTab(true);
}

void BrowserWindow::backNavigation(bool)
{
    this->mainTabsWidget->navigatePaneBack();
}

void BrowserWindow::forwardNavigation(bool)
{
    this->mainTabsWidget->navigatePaneForward();
}

void BrowserWindow::refresh()
{
    this->mainTabsWidget->refreshPane();
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

void BrowserWindow::iconChanged(const QString &address)
{
    QUrl url(address);
    QIcon icon = HeriotApplication::instance()->icon(url);
    this->setWindowIcon(icon);
}

void BrowserWindow::onOpenFile()
{
    QFileDialog fileDialog(this, QString("Open a file"));
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setVisible(true);
    if (fileDialog.exec()) {
        QList<QUrl> urls = fileDialog.selectedUrls();
        this->mainTabsWidget->setTabAddress(urls.at(0).toString());
    }
}
