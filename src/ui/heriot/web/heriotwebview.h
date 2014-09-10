#ifndef HERIOTWEBVIEW_H
#define HERIOTWEBVIEW_H

#include <QWebEngineView>

class HeriotWebPage;
class MainTabWidget;
class WebViewWrapper;

class HeriotWebView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit HeriotWebView(MainTabWidget* tabs, QWidget *parent = 0);
    WebViewWrapper* webViewWrapper() const;
    void setWebViewWrapper(WebViewWrapper* wrapper);

protected:
    QWebEngineView* createWindow(QWebEnginePage::WebWindowType type);
    void mousePressEvent(QMouseEvent* event);   // Currently unsupported in QWebEngineView
    MainTabWidget* mainTabWidget() const;

signals:
    void openNewTab(HeriotWebView* child, HeriotWebView* parent);

public slots:

private:
    HeriotWebPage* myPage;
    MainTabWidget* myTabs;
    WebViewWrapper* myWebViewWrapper;
};

#endif // HERIOTWEBVIEW_H
