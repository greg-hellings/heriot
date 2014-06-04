#ifndef MAINTABS_H
#define MAINTABS_H

#include <QWidget>

namespace Ui {
class MainTabs;
}

class OpenTab;
class QWebView;
class HeriotWebView;
class QUrl;

class MainTabsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainTabsWidget(QWidget *parent = 0);
    ~MainTabsWidget();

    HeriotWebView* newTab(bool childOfActive = false);
    void setTabAddress(const QString& location);

signals:
    void tabAddressUpdated(const QString& address);
    void tabTitleUpdated(const QString& title);

private slots:
    void urlChanged(const QUrl& url);
    void titleChanged(const QString& title);

private:
    Ui::MainTabs *ui;
    HeriotWebView* myCurrentWebView;
    OpenTab* myOpenTab;

    void setCurrentWindow(HeriotWebView* newCurrentWindow);
};

#endif // MAINTABS_H
