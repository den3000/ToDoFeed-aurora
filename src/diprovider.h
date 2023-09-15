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
public:
    unique_ptr<AppDataProvider> appDataProviderInstance() {
        return make_unique<AppDataProvider>();
    };

    unique_ptr<RestApi> restApiInstance(QString const & apiUrl) {
        return make_unique<RestApi>(apiUrl);
    };
};

#endif // DIPROVIDER_H
