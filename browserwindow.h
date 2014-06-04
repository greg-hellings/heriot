#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QVector>

class MainTabsWidget;

namespace Ui {
class BrowserWindow;
}

class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrowserWindow(QWidget *parent = 0);
    ~BrowserWindow();

public slots:
    void omniValueEntered();
    void currentTabAddressChanged(const QString& address);
    // Needs a separate title because of changing titles without nav or while changing tabs
    void currentTabTitleChanged(const QString& title);
    // User requested
    void openNewTab();
    void openNewChildTab();

private:
    Ui::BrowserWindow *ui;
    MainTabsWidget* mainTabsWidget;
};

#endif // BROWSERWINDOW_H
