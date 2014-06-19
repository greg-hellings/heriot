#ifndef HERIOTWEBVIEW_H
#define HERIOTWEBVIEW_H

#include <QWebView>

class HeriotWebPage;
class QWebInspector;

class HeriotWebView : public QWebView
{
    Q_OBJECT
public:
    explicit HeriotWebView(QWidget *parent = 0);
    QWebInspector* webInspector() const;

protected:
    QWebView* createWindow(QWebPage::WebWindowType type);
    void mousePressEvent(QMouseEvent* event);
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void openNewTab(HeriotWebView* child, HeriotWebView* parent);
    void openInspector(QWebInspector* inspector);

public slots:
    void inspect();

private:
    HeriotWebPage* myPage;
    QWebInspector* myInspector;
};

#endif // HERIOTWEBVIEW_H
