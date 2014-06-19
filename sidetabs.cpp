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
    openTab(NULL)
{
    this->ui->setupUi(this);

    this->connect(this->ui->tabs, SIGNAL(itemSelectionChanged()), SLOT(tabChanged()));

    this->ui->tabs->setFocusPolicy(Qt::NoFocus);
}

SideTabs::~SideTabs()
{
    delete ui;
}

OpenTab* SideTabs::getNewOpenTab(QWidget* content, QTreeWidgetItem *parent)
{
    return new OpenTab(parent, QString(""), content);
}

OpenTab* SideTabs::getNewOpenTab(QWidget *content, QTreeWidget *parent)
{
    return new OpenTab(parent, QString(""), content);
}

OpenTab* SideTabs::newTab(QWidget *widget, bool childOfActive, bool displayNow)
{
    OpenTab* tab = 0;
    if (childOfActive)
        tab = this->getNewOpenTab(widget, this->currentTab());
    else
        tab = this->getNewOpenTab(widget, this->ui->tabs);
    this->configureNewTab(tab);
    if (displayNow || this->openTab == NULL)
        this->setCurrentTab(tab);

    return tab;
}

OpenTab* SideTabs::newTab(QWidget *widget, QWidget *parent, bool displayNow)
{
    OpenTab* tab = this->getNewOpenTab(widget, this->findTabByWidget(parent));
    this->configureNewTab(tab);
    if (displayNow || this->openTab == NULL)
        this->setCurrentTab(tab);

    return tab;
}

void SideTabs::closeCurrentTab()
{
    OpenTab* oldTab = this->openTab;
    // Remove the webview from the stack
    this->ui->widgets->removeWidget(this->openTab->widget());
    // Promote first child to parent if one exists
    QTreeWidgetItem* newCurrent = this->openTab->removeSelf();
    // And of course we must be sure to always have some sort of tab
    if (newCurrent != NULL) {
        this->openTab = dynamic_cast<OpenTab*>(newCurrent);
        this->ui->tabs->clearSelection();
        this->openTab->setSelected(true);
    }
    emit tabChanged(oldTab, dynamic_cast<OpenTab*>(newCurrent));
}

void SideTabs::configureNewTab(OpenTab* newTab)
{
    this->ui->widgets->addWidget(newTab->widget());
}

OpenTab* SideTabs::currentTab() const
{
    return this->openTab;
}

void SideTabs::setCurrentTab(OpenTab* newTab)
{
    OpenTab* oldTab = this->openTab;
    this->openTab = newTab;
    if (!newTab->isSelected())
        newTab->setSelected(true);
    this->ui->widgets->setCurrentWidget(newTab->widget());
    emit tabChanged(oldTab, newTab);
}

void SideTabs::setCurrentWidget(QWidget *newCurrentWidget)
{
    OpenTab* newTab = this->findTabByWidget(newCurrentWidget);
    if (newTab != NULL) {
        this->setCurrentTab(newTab);
    }
}

void SideTabs::tabChanged()
{
    QList<QTreeWidgetItem*> tabs = this->ui->tabs->selectedItems();
    // I don't yet know how to grok multiple tab selection and we'll deal with a default
    // selection at a later time, if deselection is possible
    if (tabs.count() == 1) {
        OpenTab* tab = dynamic_cast<OpenTab*>(tabs.at(0));
        this->setCurrentTab(tab);
    }
}

OpenTab* SideTabs::findTabByWidget(QWidget *view)
{
    QTreeWidgetItem* item = this->ui->tabs->invisibleRootItem();
    return this->findTabByWidgetRecursion(item, view);
}

OpenTab* SideTabs::findTabByWidgetRecursion(QTreeWidgetItem* item, QWidget* view)
{
    bool found = false;
    for (int i = 0; i < item->childCount() && !found; ++i) {
        OpenTab* tab = dynamic_cast<OpenTab*>(item->child(i));
        if (tab->widget() == view) {
            return tab;
        }
        tab = this->findTabByWidgetRecursion(tab, view);
        if (tab != NULL) {
            return tab;
        }
    }

    return NULL;
}
