#include "webviewwrapper.h"
#include "heriotwebview.h"
#include <QSplitter>
#include <QWebInspector>

WebViewWrapper::WebViewWrapper(QWidget *parent) :
    QWidget(parent)
{
    this->splitter = new QSplitter(Qt::Vertical, this);
}

void WebViewWrapper::addWebView(HeriotWebView *view)
{
    this->o_webView = view;
    this->splitter->insertWidget(1, view);
    this->addWebInspector(view->webInspector());
}

void WebViewWrapper::addWebInspector(QWebInspector *inspector)
{
    this->o_webInspector = inspector;
    this->splitter->insertWidget(2, inspector);
}

HeriotWebView* WebViewWrapper::webView() const
{
    return this->o_webView;
}

QWebInspector* WebViewWrapper::webInspector() const
{
    return this->o_webInspector;
}
