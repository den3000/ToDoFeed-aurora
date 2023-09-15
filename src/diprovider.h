#ifndef DIPROVIDER_H
#define DIPROVIDER_H

#include "istartdiprovider.h"
#include "ihomediprovider.h"
#include "appdataprovider.h"

class DiProvider:
        public IStartDiProvider,
        public IHomeDiProvider
{
public:
    unique_ptr<AppDataProvider> appDataProviderInstance() {
        return make_unique<AppDataProvider>();
    };
};

#endif // DIPROVIDER_H
