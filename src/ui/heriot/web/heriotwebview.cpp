#include "heriotwebview.h"

#include <QMouseEvent>
#include <QWebInspector>
#include <QMenu>
#include <QWebSettings>
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
    this->myInspector = new QWebInspector(this);
//    this->myInspector->setPage(this->myPage);
    this->myInspector->setVisible(true);
    this->myInspector->hide();
}

QWebInspector* HeriotWebView::webInspector() const
{
    return this->myInspector;
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
    if (type == QWebEnginePage::WebBrowserWindow) {
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

void HeriotWebView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu* menu = this->myPage->createStandardContextMenu();
    menu->move(event->globalX(), event->globalY());
//    menu->removeAction(this->pageAction(QWebEnginePage::InspectElement));
    menu->addAction("Inspect", this, SLOT(inspect()));
    menu->setVisible(true);
}

void HeriotWebView::inspect()
{
//    this->myPage->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    this->myInspector->show();

    emit openInspector(this->myInspector);
}
