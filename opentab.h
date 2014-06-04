#ifndef OPENTAB_H
#define OPENTAB_H

#include <QObject>
#include <QTreeWidgetItem>

#include "heriotwebview.h"

class QTreeWidget;

class OpenTab : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:
    OpenTab(QTreeWidget* parent, const QString& text, HeriotWebView* view);
    OpenTab(QTreeWidgetItem* parent, const QString& text, HeriotWebView* view);

    HeriotWebView* webView() const;
signals:

public slots:
    void on_View_LoadFinished(bool ok);

private:
    void bind(const HeriotWebView* view);
    HeriotWebView* myWebView;
};

#endif // OPENTAB_H
