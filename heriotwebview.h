#ifndef HERIOTWEBVIEW_H
#define HERIOTWEBVIEW_H

#include <QWebView>

class HeriotWebView : public QWebView
{
    Q_OBJECT
public:
    explicit HeriotWebView(QWidget *parent = 0);

protected:
    QWebView* createWindow(QWebPage::WebWindowType type);

signals:
    void openNewTab(HeriotWebView* child, HeriotWebView* parent);

public slots:

};

#endif // HERIOTWEBVIEW_H
