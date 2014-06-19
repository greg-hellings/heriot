#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include "opentab.h"

class HeriotWebView;

class BrowserTab : public OpenTab
{
    Q_OBJECT
public:
    BrowserTab(QTreeWidget* parent, const QString& text, HeriotWebView* view);
    BrowserTab(QTreeWidgetItem* parent, const QString& text, HeriotWebView* view);
    HeriotWebView* webView() const;
signals:

public slots:
    void loadFinished(bool ok);
    void titleChanged(const QString& title);
    void iconChanged();

private:
    void bind(const HeriotWebView* view);
};

#endif // BROWSERTAB_H