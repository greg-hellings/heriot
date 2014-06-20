#ifndef HERIOTAPPLICATION_H
#define HERIOTAPPLICATION_H

#include <QApplication>
#include <QIcon>

class QUrl;

class HeriotApplication : public QApplication
{
    Q_OBJECT
public:
    HeriotApplication(int& argc, char** argv);

    static HeriotApplication* instance();

    QIcon icon(const QUrl& url);
signals:

public slots:
    void postLaunch();

private:
    QIcon defaultIcon;
};

#endif // HERIOTAPPLICATION_H
