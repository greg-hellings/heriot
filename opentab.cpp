#include "opentab.h"

#include <QTreeWidgetItem>

OpenTab::OpenTab(QTreeWidget* parent, const QString& text, const HeriotWebView* view) :
    QTreeWidgetItem(parent, QStringList(text)),
    myWebView(view)
{
    this->bind(view);
}

OpenTab::OpenTab(QTreeWidgetItem* parent, const QString& text, const HeriotWebView* view) :
    QTreeWidgetItem(parent, QStringList(text)),
    myWebView(view)
{
    this->bind(view);
}

void OpenTab::bind(const HeriotWebView *view)
{
    QObject::connect(dynamic_cast<const QObject*>(view), SIGNAL(loadFinished(bool)), dynamic_cast<const QObject*>(this), SLOT(on_View_LoadFinished(bool)));
}

void OpenTab::on_View_LoadFinished(bool ok)
{
    if (ok) {
        this->setText(0, this->myWebView->title());
    } else {
        this->setText(0, QString("Error"));
    }
}

const HeriotWebView* OpenTab::webView() const
{
    return this->myWebView;
}
