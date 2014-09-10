#include "heriotwebview.h"

#include <QMouseEvent>
//#include <QWebInspector>
#include <QMenu>
#include <QtWebEngine>
#include <QDockWidget>

#include "heriotwebpage.h"
#include "webviewwrapper.h"
#include "src/ui/heriot/tabs/maintabwidget.h"

HeriotWebView::HeriotWebView(MainTabWidget* tabs, QWidget *parent) :
    QWebEngineView(parent),
    myTabs(tabs)
{
    this->myPage = new HeriotWebPage(this);
    this->setPage(this->myPage);
}

MainTabWidget* HeriotWebView::mainTabWidget() const
{
    return this->myTabs;
}

WebViewWrapper* HeriotWebView::webViewWrapper() const
{
    return this->myWebViewWrapper;
}

void HeriotWebView::setWebViewWrapper(WebViewWrapper *wrapper)
{
    this->myWebViewWrapper = wrapper;
}


QWebEngineView* HeriotWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    if (type == QWebEnginePage::WebBrowserWindow || type == QWebEnginePage::WebBrowserTab) {
        HeriotWebView* view = this->mainTabWidget()->getNewWebView();
        emit openNewTab(view, this);
        return view;
    } else {
        return QWebEngineView::createWindow(type);
    }
}

void HeriotWebView::mousePressEvent(QMouseEvent *event)
{
    this->myPage->m_keyboardModifiers = event->modifiers();
    this->myPage->m_pressedButtons    = event->buttons();
    QWebEngineView::mousePressEvent(event);
}
