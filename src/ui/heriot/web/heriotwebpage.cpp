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

bool HeriotWebPage::certificateError(const QWebEngineCertificateError &certificateError)
{
    return true;
}
