#ifndef WEBVIEWWRAPPER_H
#define WEBVIEWWRAPPER_H

#include <QWidget>

class HeriotWebView;
class QSplitter;

class WebViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit WebViewWrapper(QWidget *parent = 0);

    void addWebView(HeriotWebView* view);
//    void addWebInspector(QWebInspector* inspector);

    HeriotWebView* webView() const;
//    QWebInspector* webInspector() const;
signals:

public slots:

private:
    QSplitter* splitter;
    HeriotWebView* o_webView;
//    QWebInspector* o_webInspector;
};

#endif // WEBVIEWWRAPPER_H
