#ifndef HERIOTWEBVIEW_H
#define HERIOTWEBVIEW_H

#include <QWebView>

class HeriotWebPage;

class HeriotWebView : public QWebView
{
    Q_OBJECT
public:
    explicit HeriotWebView(QWidget *parent = 0);

protected:
    QWebView* createWindow(QWebPage::WebWindowType type);
    void mousePressEvent(QMouseEvent* event);

signals:
    void openNewTab(HeriotWebView* child, HeriotWebView* parent);

public slots:

private:
    HeriotWebPage* myPage;
};

#endif // HERIOTWEBVIEW_H
