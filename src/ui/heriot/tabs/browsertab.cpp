#include "browsertab.h"
#include "src/ui/heriot/web/heriotwebview.h"
#include "src/heriotapplication.h"
#include "src/ui/heriot/web/webviewwrapper.h"
#include "src/settings/tabsettings.h"

#include <QTreeWidgetItem>

BrowserTab::BrowserTab(QTreeWidget* parent, const QString& text, WebViewWrapper* view) :
    OpenTab(parent, text, view)
{
    this->bind(view->webView());
}

BrowserTab::BrowserTab(QTreeWidgetItem *parent, const QString &text, WebViewWrapper* view) :
    OpenTab(parent, text, view)
{
    this->bind(view->webView());
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
        this->setText(0, this->webView()->title());
    } else {
        this->setText(0, QString("Error"));
    }
}

HeriotWebView* BrowserTab::webView() const
{
    WebViewWrapper* wrapper = dynamic_cast<WebViewWrapper*>(this->widget());
    if (wrapper != NULL)
        return wrapper->webView();
    else
        return NULL;
}

TabSetting* BrowserTab::tabSetting() const
{
    TabSetting* tabSetting = new TabSetting();
    tabSetting->setUrl(this->webView()->url().toString());
    TabSettingList tabSettingList;
    for (int i = 0; i < this->childCount(); ++i) {
        tabSettingList.append((dynamic_cast<BrowserTab*>(this->child(i)))->tabSetting());
    }
    tabSetting->setChildren(tabSettingList);
    return tabSetting;
}

void BrowserTab::titleChanged(const QString &title)
{
    this->setText(0, title);
}

void BrowserTab::iconChanged()
{
    if (this->webView() != NULL) {
        QIcon icon = HeriotApplication::instance()->icon(this->webView()->url());

        this->setIcon(0, icon);
    }
}
