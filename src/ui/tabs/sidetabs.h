#ifndef MAINTABS_H
#define MAINTABS_H

#include <QWidget>
#include <QList>

namespace Ui {
class SideTabs;
}

class OpenTab;
class QTreeWidgetItem;
class QTreeWidget;

class SideTabs : public QWidget
{
    Q_OBJECT
public:
    explicit SideTabs(QWidget *parent = 0);
    ~SideTabs();

    OpenTab* newTab(QWidget* widget, bool childOfActive = false, bool displayNow = true);
    OpenTab* newTab(QWidget* widget, QWidget* parent, bool displayNow = true);

    void closeCurrentTab(bool suppressSignals = false);

    OpenTab* currentTab() const;
    void setCurrentTab(OpenTab* tab);
    QList<OpenTab*>* openTabs();
signals:
    void tabChanged(OpenTab* oldTab, OpenTab* newTab);
    void closedTab(int topLevelTabsRemaining);

private slots:
    void tabChanged();

private:
    Ui::SideTabs *ui;
    OpenTab* openTab;
    OpenTab* findTabByWidgetRecursion(QTreeWidgetItem* item, QWidget* widget);

protected:
    OpenTab* findTabByWidget(QWidget* widget);
    void setCurrentWidget(QWidget* newCurrent);
    virtual void configureNewTab(OpenTab* newTab);
    virtual OpenTab* getNewOpenTab(QWidget* content, QTreeWidgetItem* parent);
    virtual OpenTab* getNewOpenTab(QWidget* content, QTreeWidget* parent);
};

#endif // MAINTABS_H
