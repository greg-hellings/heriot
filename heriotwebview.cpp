#include "heriotwebview.h"

#include <QMouseEvent>

#include "heriotwebpage.h"

HeriotWebView::HeriotWebView(QWidget *parent) :
    QWebView(parent)
{
    this->myPage = new HeriotWebPage(this);
    this->setPage(this->myPage);
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
