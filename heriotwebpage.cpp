#include "heriotwebpage.h"
#include "heriotwebview.h"
#include "maintabswidget.h"

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
        while(widget != NULL && !dynamic_cast<MainTabsWidget*>(widget->parent())) {
            widget = widget->parent();
        }
        if (widget != NULL) {
            MainTabsWidget* parent = dynamic_cast<MainTabsWidget*>(widget->parent());
            HeriotWebView* webView = parent->newTab(true, false);
            webView->load(request);

            return false;
        }
    }
    return QWebPage::acceptNavigationRequest(frame, request, type);
}
