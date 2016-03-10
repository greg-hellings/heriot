#include "heriotwebpage.h"
#include "heriotwebview.h"
#include "src/ui/heriot/tabs/maintabwidget.h"
#include "src/ui/tabs/opentab.h"
#include "src/ui/heriot/tabs/browsertab.h"

HeriotWebPage::HeriotWebPage(QWidget *parent) :
    QWebPage(parent),
    m_keyboardModifiers(Qt::NoModifier),
    m_pressedButtons(Qt::NoButton)
{
}

bool HeriotWebPage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type)
{
    // First we handle whether the user was requesting a specific opening
    if (type == QWebPage::NavigationTypeLinkClicked && ( this->m_keyboardModifiers & Qt::ControlModifier || this->m_pressedButtons == Qt::MidButton ) ) {
        QObject*        widget = this;
        while(widget != NULL && !dynamic_cast<MainTabWidget*>(widget->parent())) {
            widget = widget->parent();
        }
        if (widget != NULL) {
            MainTabWidget* parent = dynamic_cast<MainTabWidget*>(widget->parent());
            BrowserTab* tab = dynamic_cast<BrowserTab*>(parent->newTab(parent->getNewWebView(), true, false));
            HeriotWebView* webView = tab->webView();
            webView->load(request);

            return false;
        }
    }
    return QWebPage::acceptNavigationRequest(frame, request, type);
}
