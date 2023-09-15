#ifndef ISTARTDIPROVIDER_H
#define ISTARTDIPROVIDER_H

#include "easy_import.h"

struct IStartDiProvider {
    unique_ptr<QString> someStart() {
        return make_unique<QString>("start");
    }
};

#endif // ISTARTDIPROVIDER_H
