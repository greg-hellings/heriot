#include "browserwindow.h"
#include "ui_browserwindow.h"
#include "maintabwidget.h"
#include "heriotapplication.h"
#include "heriotwebview.h"

#include <QWebView>
#include <QTabWidget>
#include <QKeyEvent>
#include <QDockWidget>
#include <QWebInspector>

BrowserWindow::BrowserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrowserWindow)
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

    this->connect(this->ui->backButton, SIGNAL(clicked(bool)), SLOT(backNavigation(bool)));
    this->connect(this->ui->forwardButton, SIGNAL(clicked(bool)), SLOT(forwardNavigation(bool)));

    this->connect(this->ui->actionExit, SIGNAL(triggered()), SLOT(quit()));
    this->connect(this->ui->actionClose_Window, SIGNAL(triggered()), SLOT(close()));
    this->connect(this->ui->actionNew_Window, SIGNAL(triggered()), SLOT(newWindow()));

    this->connect(this->ui->actionClose_Tab, SIGNAL(triggered()), SLOT(onCloseCurrentTab()));

    this->setIconSize(QSize(16, 16));
}

BrowserWindow::~BrowserWindow()
{
    delete ui;
}

void BrowserWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_L:
        if (event->modifiers() & Qt::ControlModifier) {
            this->ui->omniBox->setFocus();
        }
        event->ignore();
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

void BrowserWindow::openNewTab()
{
    this->mainTabsWidget->newTab(new HeriotWebView(this->mainTabsWidget));
    this->ui->omniBox->setFocus();
}

void BrowserWindow::openNewChildTab()
{
    this->mainTabsWidget->newTab(new HeriotWebView(this->mainTabsWidget), true);
    this->ui->omniBox->setFocus();
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

void BrowserWindow::iconChanged(const QString &address)
{
    QUrl url(address);
    QIcon icon = HeriotApplication::instance()->icon(url);
    this->setWindowIcon(icon);
}/*

void BrowserWindow::openInspector(QWebInspector* inspector)
{
    QDockWidget* dockWidget = new QDockWidget(QString("Inspector"), this);
    dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockWidget->setWidget(inspector);
    dockWidget->setVisible(true);
}*/