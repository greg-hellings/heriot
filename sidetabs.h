#ifndef MAINTABS_H
#define MAINTABS_H

#include <QWidget>

namespace Ui {
class SideTabs;
}

class OpenTab;
class QTreeWidgetItem;

class SideTabs : public QWidget
{
    Q_OBJECT
public:
    explicit SideTabs(QWidget *parent = 0);
    ~SideTabs();

    OpenTab* newTab(bool childOfActive = false, bool displayNow = true);
    OpenTab* newTab(QWidget* widget, bool childOfActive = false, bool displayNow = true);
    OpenTab* newTab(QWidget* widget, QWidget* parent, bool displayNow = true);

    void closeCurrentTab();

    OpenTab* currentTab() const;
signals:
    void tabChanged(OpenTab* current);

private slots:
    void tabChanged();

private:
    Ui::SideTabs *ui;
    QWidget* currentWidget;
    OpenTab* openTab;
    OpenTab* findTabByWidgetRecursion(QTreeWidgetItem* item, QWidget* widget);

protected:
    OpenTab* findTabByWidget(QWidget* widget);
    void setCurrentWidget(QWidget* newCurrent);
    void configureNewTab(OpenTab* newTab);
};

#endif // MAINTABS_H
