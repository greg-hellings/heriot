#include "src/web/cookiejar.h"

CookieJar::CookieJar(QObject *parent) :
    QNetworkCookieJar(parent)
{
}
