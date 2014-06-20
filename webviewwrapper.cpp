#include "webviewwrapper.h"
#include "heriotwebview.h"
#include <QSplitter>
#include <QWebInspector>
#include <QGridLayout>

WebViewWrapper::WebViewWrapper(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    this->setLayout(layout);
    this->splitter = new QSplitter(Qt::Vertical, this);
    this->splitter->setChildrenCollapsible(false);
    this->setStyleSheet(QString("QWidget {margin: 0px; padding: 0px;}"));
    layout->addWidget(this->splitter);
    layout->setMargin(0);
}

void WebViewWrapper::addWebView(HeriotWebView *view)
{
    this->o_webView = view;
    this->splitter->insertWidget(0, view);
    this->addWebInspector(view->webInspector());
}

void WebViewWrapper::addWebInspector(QWebInspector *inspector)
{
    this->o_webInspector = inspector;
    this->splitter->insertWidget(1, inspector);
}

HeriotWebView* WebViewWrapper::webView() const
{
    return this->o_webView;
}

QWebInspector* WebViewWrapper::webInspector() const
{
    return this->o_webInspector;
}
