#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include "src/ui/tabs/opentab.h"

class WebViewWrapper;
class HeriotWebView;
class TabSetting;

class BrowserTab : public OpenTab
{
    Q_OBJECT
public:
    BrowserTab(QTreeWidget* parent, const QString& text, WebViewWrapper* view);
    BrowserTab(QTreeWidgetItem* parent, const QString& text, WebViewWrapper* view);
    HeriotWebView* webView() const;
    TabSetting* tabSetting() const;
signals:

public slots:
    void loadFinished(bool ok);
    void titleChanged(const QString& title);
    void iconChanged(const QUrl& url);
    void iconChanged();

private:
    void bind(const HeriotWebView* view);
};

#endif // BROWSERTAB_H
