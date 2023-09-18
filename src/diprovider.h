#ifndef DIPROVIDER_H
#define DIPROVIDER_H

#include "appdataprovider.h"
#include "restapi.h"
#include "istartdiprovider.h"
#include "ihomediprovider.h"

class DiProvider:
        public IStartDiProvider,
        public IHomeDiProvider
{
    shared_ptr<AppDataProvider> m_appDataProvider;
    shared_ptr<RestApi> m_restApi;
public:

    explicit DiProvider()
        : m_appDataProvider { make_shared<AppDataProvider>() }
        , m_restApi { make_shared<RestApi>(m_appDataProvider.get()->apiUrl()) }
    { qDebug(); }

    ~DiProvider() { qDebug(); }

    shared_ptr<ILoginStateProvider> loginStateProvider() { return m_appDataProvider; };

    // IStartDiProvide, IHomeDiProvider interface
    shared_ptr<RestApi> restApi() override { return m_restApi; }

    // IStartDiProvide interface
    shared_ptr<ILoginTokenProvider> loginTokenProvider() override { return m_appDataProvider; };

    // IHomeDiProvider interface
    shared_ptr<ITokenValueProvider> tokenValueProvider() override { return m_appDataProvider; }
    shared_ptr<ILogoutTokenProvider> logoutTokenProvider() override { return m_appDataProvider; };
};

#endif // DIPROVIDER_H
