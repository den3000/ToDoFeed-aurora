#ifndef APPDATAPROVIDER_H
#define APPDATAPROVIDER_H

#include <QFile>

#include "easy_import.h"

#include "ilogintokenprovider.h"
#include "ilogouttokenprovider.h"

#include "smoozyutils.h"

struct ILoginStateProvider {
    virtual bool isLoggedIn() = 0;
};

struct IApiUrlProvider{
    virtual QString apiUrl() = 0;
};

class AppDataProvider:
        public ILoginStateProvider,
        public ILoginTokenProvider,
        public ILogoutTokenProvider,
        public IApiUrlProvider
{
public:

    QString token() { return Smoozy::settings().value("token").toString(); };

    // ILoginStateProvider interface
    bool isLoggedIn() override { return Smoozy::settings().contains("token"); };

    // ILogoutTokenProvider interface
    void logout() override { Smoozy::settings().remove("token"); };

    // ILoginTokenProvider interface
    void login(const QString &token) override
        { Smoozy::settings().setValue("token", QVariant::fromValue(token)); };

    // IApiUrlProvider interface
    QString apiUrl() override {
        // excluded in .git/info/exclude
        QFile f(":api.endpoint");
        f.open(QIODevice::ReadOnly);
        return QString(f.readAll());
    };
};
#endif // APPDATAPROVIDER_H
