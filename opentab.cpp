#include "opentab.h"

#include <QTreeWidgetItem>

OpenTab::OpenTab(QTreeWidget* parent, const QString& text, HeriotWebView* view) :
    QTreeWidgetItem(parent, QStringList(text)),
    myWebView(view)
{
    this->bind(view);
}

OpenTab::OpenTab(QTreeWidgetItem* parent, const QString& text, HeriotWebView* view) :
    QTreeWidgetItem(parent, QStringList(text)),
    myWebView(view)
{
    this->bind(view);
}

void OpenTab::bind(const HeriotWebView *view)
{
    QObject::connect(dynamic_cast<const QObject*>(view), SIGNAL(loadFinished(bool)), dynamic_cast<const QObject*>(this), SLOT(on_View_LoadFinished(bool)));
    this->connect(view, SIGNAL(titleChanged(QString)), SLOT(titleChanged(QString)));
}

void OpenTab::on_View_LoadFinished(bool ok)
{
    if (ok) {
        this->setText(0, this->myWebView->title());
    } else {
        this->setText(0, QString("Error"));
    }
}

HeriotWebView* OpenTab::webView() const
{
    return this->myWebView;
}

void OpenTab::titleChanged(const QString &title)
{
    this->setText(0, title);
}
