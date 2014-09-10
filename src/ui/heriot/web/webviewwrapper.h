#ifndef WEBVIEWWRAPPER_H
#define WEBVIEWWRAPPER_H

#include <QWidget>
#include <QWebEngineView>

class HeriotWebView;
class QSplitter;
class QLineEdit;

class WebViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit WebViewWrapper(QWidget *parent = 0);
    ~WebViewWrapper();

    void addWebView(HeriotWebView* view);

    HeriotWebView* webView() const;
signals:

public slots:
    void searchNext();
    void searchPrevious();
    void searchChanged();

private:
    void addSearchView();
    QWebEnginePage::FindFlag searchFlags();
    QWebEnginePage::FindFlag searchFlagsBackwards();

    QSplitter* splitter;
    HeriotWebView* o_webView;
    QWidget* o_searchView;
    QLineEdit* o_searchLineEdit;
};

#endif // WEBVIEWWRAPPER_H
