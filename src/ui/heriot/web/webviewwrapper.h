#ifndef WEBVIEWWRAPPER_H
#define WEBVIEWWRAPPER_H

#include <QWidget>
#include <QWebView>

class HeriotWebView;
class QWebInspector;
class QSplitter;
class QLineEdit;

class WebViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit WebViewWrapper(QWidget *parent = 0);
    ~WebViewWrapper();

    void addWebView(HeriotWebView* view);
    void addWebInspector(QWebInspector* inspector);

    HeriotWebView* webView() const;
    QWebInspector* webInspector() const;
signals:

public slots:
    void searchNext();
    void searchPrevious();
    void searchChanged();

private:
    void addSearchView();
    QWebPage::FindFlag searchFlags();
    QWebPage::FindFlag searchFlagsBackwards();

    QSplitter* splitter;
    HeriotWebView* o_webView;
    QWebInspector* o_webInspector;
    QWidget* o_searchView;
    QLineEdit* o_searchLineEdit;
};

#endif // WEBVIEWWRAPPER_H
