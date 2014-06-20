#include "src/ui/windows/browser/browserwindow.h"
#include <QApplication>
#include "heriotapplication.h"

int main(int argc, char *argv[])
{
    HeriotApplication a(argc, argv);
    BrowserWindow w;
    w.show();

    return a.exec();
}
