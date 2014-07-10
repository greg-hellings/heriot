#ifndef HERIOTWEBPAGE_H
#define HERIOTWEBPAGE_H

#include <QWebEnginePage>

#include "heriotwebview.h"

class HeriotWebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit HeriotWebPage(QWidget *parent = 0);

signals:

public slots:

protected:
    QWebEnginePage* createWindow(WebWindowType type);

private:
    friend class HeriotWebView;

    Qt::KeyboardModifiers m_keyboardModifiers;
    Qt::MouseButtons      m_pressedButtons;
};

#endif // HERIOTWEBPAGE_H
