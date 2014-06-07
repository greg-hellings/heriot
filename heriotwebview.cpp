#include "heriotwebview.h"

HeriotWebView::HeriotWebView(QWidget *parent) :
    QWebView(parent)
{
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
