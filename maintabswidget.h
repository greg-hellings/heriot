#ifndef MAINTABS_H
#define MAINTABS_H

#include <QWidget>

namespace Ui {
class MainTabs;
}

class OpenTab;
class QWebView;
class QWebHistoryItem;
class HeriotWebView;
class QUrl;
class QTreeWidgetItem;

class MainTabsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainTabsWidget(QWidget *parent = 0);
    ~MainTabsWidget();

    HeriotWebView* newTab(bool childOfActive = false, bool displayNow = true);
    void setTabAddress(const QString& location);

    void navigatePaneBack();
    void navigatePaneForward();
signals:
    void tabAddressUpdated(const QString& address);
    void tabTitleUpdated(const QString& title);
    void iconChanged(const QString& address);

private slots:
    void urlChanged(const QUrl& url);
    void titleChanged(const QString& title);
    void tabChanged();
    void iconChanged();
    void openNewTab(HeriotWebView* child, HeriotWebView* parent);

private:
    Ui::MainTabs *ui;
    HeriotWebView* myCurrentWebView;
    OpenTab* myOpenTab;

    void setCurrentWindow(HeriotWebView* newCurrentWindow);
    void configureNewTab(HeriotWebView* webView);
    OpenTab* findTabByView(HeriotWebView* view);
    OpenTab* findTabByViewRecursion(QTreeWidgetItem* item, HeriotWebView* view);
};

#endif // MAINTABS_H
