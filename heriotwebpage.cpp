#include "heriotwebpage.h"
#include "heriotwebview.h"
#include "maintabwidget.h"
#include "opentab.h"

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
            OpenTab* tab = parent->newTab(new HeriotWebView(parent), true, false);
            HeriotWebView* webView = dynamic_cast<HeriotWebView*>(tab->widget());
            webView->load(request);

            return false;
        }
    }
    return QWebPage::acceptNavigationRequest(frame, request, type);
}
