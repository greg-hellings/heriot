#include "opentab.h"
#include "heriotapplication.h"

#include <QTreeWidgetItem>
#include <QTimer>

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
    this->connect(view, SIGNAL(iconChanged()), SLOT(iconChanged()));
    this->connect(view, SIGNAL(loadFinished(bool)), SLOT(iconChanged()));
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

void OpenTab::iconChanged()
{
    QIcon icon = HeriotApplication::instance()->icon(this->myWebView->url());

    this->setIcon(0, icon);
}
