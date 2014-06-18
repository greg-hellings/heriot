#include "browsertab.h"
#include "heriotwebview.h"

#include <QTreeWidgetItem>

BrowserTab::BrowserTab(QTreeWidget* parent, const QString& text, HeriotWebView* view) :
    OpenTab(parent, text, view)
{
    this->bind(view);
}

void BrowserTab::bind(const HeriotWebView *view)
{
    QObject::connect(dynamic_cast<const QObject*>(view), SIGNAL(loadFinished(bool)), dynamic_cast<const QObject*>(this), SLOT(loadFinished(bool)));
    this->connect(view, SIGNAL(titleChanged(QString)), SLOT(titleChanged(QString)));
    this->connect(view, SIGNAL(iconChanged()), SLOT(iconChanged()));
    this->connect(view, SIGNAL(loadFinished(bool)), SLOT(iconChanged()));
    this->connect(view, SIGNAL(loadStarted()), SLOT(iconChanged()));
}

void BrowserTab::loadFinished(bool ok)
{
    if (ok) {
        this->setText(0, this->myWebView->title());
    } else {
        this->setText(0, QString("Error"));
    }
}

HeriotWebView* BrowserTab::webView() const
{
    return dynamic_cast<HeriotWebView*>(this->widget());
}

void BrowserTab::titleChanged(const QString &title)
{
    this->setText(0, title);
}

void BrowserTab::iconChanged()
{
    QIcon icon = HeriotApplication::instance()->icon(this->myWebView->url());

    this->setIcon(0, icon);
}
