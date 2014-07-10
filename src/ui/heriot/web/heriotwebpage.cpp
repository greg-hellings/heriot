#include "heriotwebpage.h"
#include "heriotwebview.h"
#include "src/ui/heriot/tabs/maintabwidget.h"
#include "src/ui/tabs/opentab.h"
#include "src/ui/heriot/tabs/browsertab.h"

HeriotWebPage::HeriotWebPage(QWidget *parent) :
    QWebEnginePage(parent),
    m_keyboardModifiers(Qt::NoModifier),
    m_pressedButtons(Qt::NoButton)
{
}

QWebEnginePage* HeriotWebPage::createWindow(WebWindowType type)
{
    QObject*        widget = this;
    while(widget != NULL && !dynamic_cast<MainTabWidget*>(widget->parent())) {
        widget = widget->parent();
    }
    if (widget != NULL) {
        MainTabWidget* parent = dynamic_cast<MainTabWidget*>(widget->parent());
        BrowserTab* tab = dynamic_cast<BrowserTab*>(parent->newTab(parent->getNewWebView(), true, false));
        return tab->webView()->page();
    }
    return NULL;
}
