#include "heriotwebview.h"

#include <QMouseEvent>
#include <QWebInspector>
#include <QMenu>
#include <QWebSettings>
#include <QDockWidget>

#include "heriotwebpage.h"

HeriotWebView::HeriotWebView(QWidget *parent) :
    QWebView(parent)
{
    this->myPage = new HeriotWebPage(this);
    this->setPage(this->myPage);
    this->myInspector = new QWebInspector();
    this->myInspector->setPage(this->myPage);
}

QWebView* HeriotWebView::createWindow(QWebPage::WebWindowType type)
{
    if (type == QWebPage::WebBrowserWindow) {
        HeriotWebView* view = new HeriotWebView(dynamic_cast<QWidget*>(this->parent()));
        emit openNewTab(view, this);
        return view;
    } else {
        return QWebView::createWindow(type);
    }
}

void HeriotWebView::mousePressEvent(QMouseEvent *event)
{
    this->myPage->m_keyboardModifiers = event->modifiers();
    this->myPage->m_pressedButtons    = event->buttons();
    QWebView::mousePressEvent(event);
}

void HeriotWebView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu* menu = this->myPage->createStandardContextMenu();
    menu->move(event->globalX(), event->globalY());
    menu->addAction("Inspect", this, SLOT(inspect()));
    menu->setVisible(true);
}

void HeriotWebView::inspect()
{
    this->myPage->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    QWebInspector* myInspector = new QWebInspector();
    myInspector->setPage(this->myPage);
    myInspector->setVisible(true);

    emit createInspector(myInspector);
}
