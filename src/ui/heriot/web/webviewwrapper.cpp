#include "webviewwrapper.h"
#include "heriotwebview.h"
#include <QSplitter>
#include <QWebInspector>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

#define WEB_VIEW_INDEX 0
#define SEARCH_VIEW_INDEX 1
#define INSPECTOR_VIEW_INDEX 2

WebViewWrapper::WebViewWrapper(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    this->setLayout(layout);
    this->splitter = new QSplitter(Qt::Vertical, this);
    this->splitter->setChildrenCollapsible(false);
    layout->addWidget(this->splitter);
    layout->setMargin(0);
}

WebViewWrapper::~WebViewWrapper()
{
    delete this->o_searchView;
    delete this->o_searchLineEdit;
}

void WebViewWrapper::addWebView(HeriotWebView *view)
{
    this->o_webView = view;
    this->splitter->insertWidget(WEB_VIEW_INDEX, view);
    this->addSearchView();
    this->addWebInspector(view->webInspector());
    view->setWebViewWrapper(this);
}

void WebViewWrapper::addWebInspector(QWebInspector *inspector)
{
    this->o_webInspector = inspector;
    this->splitter->insertWidget(INSPECTOR_VIEW_INDEX, inspector);
}

void WebViewWrapper::addSearchView()
{
    // Create the widgets
    this->o_searchView = new QWidget(this);
    this->o_searchLineEdit = new QLineEdit(this->o_searchView);
    QPushButton* searchForward = new QPushButton("Next", this->o_searchView);
    QPushButton* searchBackward = new QPushButton("Prev", this->o_searchView);
    QLayout* layout = new QHBoxLayout(this->o_searchView);
    // Configure layout options
    layout->setMargin(0);
    this->o_searchView->setStyleSheet("QPushButton {padding: 4px}");
    this->o_searchView->setLayout(layout);
    // Attach them
    layout->addWidget(this->o_searchLineEdit);
    layout->addWidget(searchForward);
    layout->addWidget(searchBackward);
    this->splitter->insertWidget(SEARCH_VIEW_INDEX, this->o_searchView);

    // Set listeners
    this->connect(searchBackward, SIGNAL(clicked()), SLOT(searchPrevious()));
    this->connect(searchForward, SIGNAL(clicked()), SLOT(searchNext()));
    this->connect(this->o_searchLineEdit, SIGNAL(returnPressed()), SLOT(searchNext()));
    this->connect(this->o_searchLineEdit, SIGNAL(textChanged(QString)), SLOT(searchChanged()));
}

void WebViewWrapper::searchPrevious()
{
    QString query = this->o_searchLineEdit->text();
    if (query.size() > 0) {
        this->webView()->findText(query, this->searchFlagsBackwards());
    }
}

void WebViewWrapper::searchNext()
{
    QString query = this->o_searchLineEdit->text();
    if (query.size() > 0) {
        this->webView()->findText(query, this->searchFlags());
    }
}

void WebViewWrapper::searchChanged()
{
    this->webView()->findText(this->o_searchLineEdit->text());
}

QWebPage::FindFlag WebViewWrapper::searchFlags()
{
    return QWebPage::FindWrapsAroundDocument;
}

QWebPage::FindFlag WebViewWrapper::searchFlagsBackwards()
{
    return (QWebPage::FindFlag) (this->searchFlags() & QWebPage::FindBackward);
}

HeriotWebView* WebViewWrapper::webView() const
{
    return this->o_webView;
}

QWebInspector* WebViewWrapper::webInspector() const
{
    return this->o_webInspector;
}
