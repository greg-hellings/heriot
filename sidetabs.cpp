#include "sidetabs.h"
#include "ui_sidetabs.h"

#include "opentab.h"
#include "heriotwebview.h"

#include <QItemSelectionModel>
#include <QSizePolicy>
#include <QWebHistory>

SideTabs::SideTabs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideTabs()),
    myCurrentWidget(NULL)
{
    this->ui->setupUi(this);

    this->connect(this->ui->tabs, SIGNAL(itemSelectionChanged()), SLOT(tabChanged()));

    this->setCurrentWindow(this->newTab(false));

    this->ui->tabs->setFocusPolicy(Qt::NoFocus);
}

SideTabs::~SideTabs()
{
    delete ui;
}

void SideTabs::closeCurrentTab()
{
    // Remove the webview from the stack
    this->ui->widgets->removeWidget(this->openTab->widget());
    // Promote first child to parent if one exists
    QTreeWidgetItem* newCurrent = this->openTab->removeSelf();
    // And of course we must be sure to always have some sort of tab
    if (newCurrent == NULL && this->ui->tabs->invisibleRootItem()->childCount() == 0) {
        this->setCurrentWindow(this->newTab(false));
    } else if (newCurrent == NULL) {
        // nop
    } else {
        this->openTab = dynamic_cast<OpenTab*>(newCurrent);
        this->ui->tabs->clearSelection();
        this->openTab->setSelected(true);
    }
}

void SideTabs::configureNewTab(OpenTab* newTab)
{
    this->ui->widgets->addWidget(newTab->widget());
}

HeriotWebView* SideTabs::newTab(bool childOfCurrent, bool displayNow)
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

OpenTab* SideTabs::currentTab()
{
    return this->openTab;
}

void SideTabs::setCurrentWidget(QWidget *newCurrentWindow)
{
    this->myCurrentWidget = newCurrentWindow;

    this->ui->widgets->setCurrentWidget(this->myCurrentWebView);

    emit tabAddressUpdated(this->myCurrentWebView->url().toString());
    emit tabTitleUpdated(this->myCurrentWebView->title());
    emit iconChanged(this->myCurrentWebView->url().toString());
}

void SideTabs::tabChanged()
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

OpenTab* SideTabs::findTabByView(QWidget *view)
{
    QTreeWidgetItem* item = this->ui->tabs->invisibleRootItem();
    return this->findTabByViewRecursion(item, view);
}

OpenTab* SideTabs::findTabByViewRecursion(QTreeWidgetItem* item, QWidget* view)
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
