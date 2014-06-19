#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include "sidetabs.h"

class HeriotWebView;
class QWebInspector;

class MainTabWidget : public SideTabs
{
    Q_OBJECT
public:
    explicit MainTabWidget(QWidget *parent = 0);
    void setTabAddress(const QString& location);

    void navigatePaneBack();
    void navigatePaneForward();
signals:
    void tabAddressUpdated(const QString& address);
    void tabTitleUpdated(const QString& title);
    void iconChanged(const QString& address);

public slots:
    void urlChanged(const QUrl& url);
    void titleChanged(const QString& title);
    void iconChanged();
    void openNewTab(HeriotWebView *child, HeriotWebView* parent);
    void tabChanged(OpenTab* newTab, OpenTab* oldTab);
    void tabClosing(int remainingTabs);

private:
    HeriotWebView* currentWebView();

protected:
    void configureNewTab(OpenTab *newTab);
    OpenTab* getNewOpenTab(QWidget* content, QTreeWidgetItem* parent);
    OpenTab* getNewOpenTab(QWidget* content, QTreeWidget* parent);
};

#endif // MAINTABVIEW_H
