#ifndef HERIOTWEBPAGE_H
#define HERIOTWEBPAGE_H

#include <QWebPage>

#include "heriotwebview.h"

class HeriotWebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit HeriotWebPage(QWidget *parent = 0);

    bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);

signals:

public slots:

private:
    friend class HeriotWebView;

    Qt::KeyboardModifiers m_keyboardModifiers;
    Qt::MouseButtons      m_pressedButtons;
};

#endif // HERIOTWEBPAGE_H
