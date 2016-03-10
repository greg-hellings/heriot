#ifndef OPENTABS_H
#define OPENTABS_H

#include <QObject>
#include <QStandardItemModel>

class HeriotWebView;

class OpenTabs : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit OpenTabs(QObject *parent = 0);

    void addTab(const QString& location, const HeriotWebView* view);
signals:

public slots:

};

#endif // OPENTABS_H
