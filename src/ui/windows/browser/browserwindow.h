#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QVector>

class MainTabWidget;

namespace Ui {
class BrowserWindow;
}

class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrowserWindow(QWidget *parent = 0);
    ~BrowserWindow();

protected:
    void keyPressEvent(QKeyEvent *);
    void closeEvent(QCloseEvent *);

public slots:
    void omniValueEntered();
    void backNavigation(bool);
    void forwardNavigation(bool);
    void quit();
    void currentTabAddressChanged(const QString& address);
    void iconChanged(const QString& address);
    // Needs a separate title because of changing titles without nav or while changing tabs
    void currentTabTitleChanged(const QString& title);
    // User requested
    void openNewTab(bool child = false);
    void openNewChildTab();
    void newWindow();
    void onCloseCurrentTab();
    void onOpenFile();

private:
    Ui::BrowserWindow *ui;
    MainTabWidget* mainTabsWidget;
};

#endif // BROWSERWINDOW_H
