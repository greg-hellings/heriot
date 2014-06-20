#ifndef HERIOTWEBVIEW_H
#define HERIOTWEBVIEW_H

#include <QWebView>

class HeriotWebPage;
class QWebInspector;
class MainTabWidget;
class WebViewWrapper;

class HeriotWebView : public QWebView
{
    Q_OBJECT
public:
    explicit HeriotWebView(MainTabWidget* tabs, QWidget *parent = 0);
    QWebInspector* webInspector() const;
    WebViewWrapper* webViewWrapper() const;
    void setWebViewWrapper(WebViewWrapper* wrapper);

protected:
    QWebView* createWindow(QWebPage::WebWindowType type);
    void mousePressEvent(QMouseEvent* event);
    void contextMenuEvent(QContextMenuEvent *event);
    MainTabWidget* mainTabWidget() const;

signals:
    void openNewTab(HeriotWebView* child, HeriotWebView* parent);
    void openInspector(QWebInspector* inspector);

public slots:
    void inspect();

private:
    HeriotWebPage* myPage;
    QWebInspector* myInspector;
    MainTabWidget* myTabs;
    WebViewWrapper* myWebViewWrapper;
};

#endif // HERIOTWEBVIEW_H
