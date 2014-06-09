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
    this->connect(view, SIGNAL(loadStarted()), SLOT(iconChanged()));
}

OpenTab* OpenTab::closestSibling(QTreeWidgetItem* closestRelative)
{
    OpenTab* target = 0;
    if (closestRelative->childCount() > 1) {
        int myIndex = closestRelative->indexOfChild(this);
        // If this is not the oldest child, then choose the next oldest (above) child
        if (myIndex > 0) {
            target = dynamic_cast<OpenTab*>(closestRelative->child(myIndex - 1));
        } else {
            // Otherwise, choose the second oldest child
            target = dynamic_cast<OpenTab*>(closestRelative->child(1));
        }
    }

    return target;
}

OpenTab* OpenTab::removeSelf()
{
    OpenTab* closestRelative = 0;
    QTreeWidgetItem* parent = QTreeWidgetItem::parent();
    if (parent == NULL) {
        parent = this->treeWidget()->invisibleRootItem();
    }
    // If this tab has children, the eldest child is the closest relative
    if (this->childCount() > 0) {
        closestRelative = dynamic_cast<OpenTab*>(this->takeChild(0));
        // And promote that child to this one's status
        closestRelative->addChildren(this->takeChildren());
        closestRelative->setExpanded(true);
        // And promote this to the parent
        parent->insertChild(parent->indexOfChild(this), closestRelative);
    } else {
        closestRelative = dynamic_cast<OpenTab*>(parent);
        if (closestRelative != NULL) {
            // If this tab was not alone, then the closest relative is one of its siblings
            closestRelative = closestSibling(closestRelative);
        } else {
            closestRelative = closestSibling(parent);
        }
    }
    // Remove this one from its parent
    parent->removeChild(this);

    return closestRelative;
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
