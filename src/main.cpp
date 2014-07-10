#include "src/ui/windows/browser/browserwindow.h"
#include "src/settings/heriotsettings.h"
#include <QApplication>
#include <QWebEngine>
#include "heriotapplication.h"

int main(int argc, char *argv[])
{
    HeriotApplication a(argc, argv);

    QWebEngine::initialize();
    QStringList list = HeriotSettings::instance()->getWindows();
    BrowserWindow* window;
    for (QStringList::const_iterator it = list.begin(); it != list.end(); ++it) {
        window = new BrowserWindow(*it);
        window->show();
        window->activateWindow();
    }
    BrowserWindow w;
    w.show();

    return a.exec();
}
