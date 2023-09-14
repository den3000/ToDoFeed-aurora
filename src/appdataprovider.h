#ifndef APPDATAPROVIDER_H
#define APPDATAPROVIDER_H

#include "QSettings"
#include "QFile"

#include "easy_import.h"

struct ILoginTokenProvider {
    virtual void login(QString const & token) = 0;
};

struct ILogoutTokenProvider {
    virtual void logout() = 0;
};

struct IApiUrlProvider{
    virtual QString apiUrl() = 0;
};

class AppDataProvider:
        public ILoginTokenProvider,
        public ILogoutTokenProvider,
        public IApiUrlProvider
{
public:
    bool isLoggedIn() {
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        return settings.contains("token");
    };

    QString token() {
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        return settings.value("token").toString();
    };

    // ILogoutTokenProvider interface
    void logout() override {
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        settings.remove("token");
    };

    // ILoginTokenProvider interface
    void login(const QString &token) override {
        QSettings settings(QSettings::UserScope, "den3000", "ToDo Feed");
        settings.setValue("token", QVariant::fromValue(token));
    };

    // IApiUrlProvider interface
    QString apiUrl() override {
        // excluded in .git/info/exclude
        QFile f(":api.endpoint");
        f.open(QIODevice::ReadOnly);
        return QString(f.readAll());
    };
};
#endif // APPDATAPROVIDER_H
