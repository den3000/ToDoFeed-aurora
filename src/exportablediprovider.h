#ifndef EXPORTABLEDIPROVIDER_H
#define EXPORTABLEDIPROVIDER_H

#include <QObject>

#include "appdataprovider.h"
#include "ilogouttokenprovider.h"
#include "restapi.h"

#include "startservice.h"
#include "profileservice.h"
#include "startvm.h"
#include "loginvm.h"
#include "editprofilevm.h"

class ExportableDiProvider: public QObject
{
    Q_OBJECT

    shared_ptr<AppDataProvider> m_appDataProvider;
    shared_ptr<RestApi> m_restApi;

    shared_ptr<StartService> m_startService;
    shared_ptr<StartService> lazyStartService() {
        if(!m_startService) {
            m_startService = startServiceInstance();
        }
        return m_startService;
    };

    shared_ptr<ProfileService> m_profileService;
    shared_ptr<ProfileService> lazyProfileService() {
        if(!m_profileService) {
            m_profileService = profileServiceInstance();
        }
        return m_profileService;
    };

public:

    explicit ExportableDiProvider(QObject * parent = nullptr)
        : QObject(parent)
        , m_appDataProvider { make_shared<AppDataProvider>() }
        , m_restApi { make_shared<RestApi>(m_appDataProvider.get()->apiUrl()) }
    { qDebug(); }
    ~ExportableDiProvider() { qDebug(); }

    unique_ptr<StartService> startServiceInstance()
        { return make_unique<StartService>(m_restApi); }

    unique_ptr<ProfileService> profileServiceInstance()
        { return make_unique<ProfileService>(m_restApi, tokenValueProvider()); }

    shared_ptr<ILoginTokenProvider> loginTokenProvider() { return m_appDataProvider; };

    shared_ptr<ILogoutTokenProvider> logoutTokenProvider() { return m_appDataProvider; };

    shared_ptr<ITokenValueProvider> tokenValueProvider() { return m_appDataProvider; };

    Q_INVOKABLE StartVM * startVmInstance()
        { return new StartVM(); }

    Q_INVOKABLE LoginVM * loginVmInstance()
        { return new LoginVM(loginTokenProvider(), lazyStartService()); }

    Q_INVOKABLE EditProfileVM * signupVmInstance()
        { return new EditProfileVM(loginTokenProvider(), lazyStartService()); }

    Q_INVOKABLE EditProfileVM * editProfileVmInstance()
        { return new EditProfileVM(logoutTokenProvider(), lazyProfileService()); }
};
#endif // EXPORTABLEDIPROVIDER_H
