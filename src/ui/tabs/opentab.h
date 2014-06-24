#ifndef OPENTAB_H
#define OPENTAB_H

#include <QObject>
#include <QTreeWidgetItem>

#include "src/ui/heriot/web/heriotwebview.h"

class QTreeWidget;

class OpenTab : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:
    OpenTab(QTreeWidget* parent, const QString& text, QWidget* view);
    OpenTab(QTreeWidgetItem* parent, const QString& text, QWidget* view);

    QWidget* widget() const;
    OpenTab* removeSelf();

    OpenTab* closestSibling(QTreeWidgetItem* closestRelative);
    void addChildren(const QList<QTreeWidgetItem *> &children);
signals:

public slots:

private:
    QWidget* myWidget;
    QTreeWidgetItem* up;
};

#endif // OPENTAB_H
