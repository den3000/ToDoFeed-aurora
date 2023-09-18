#ifndef ITOKENVALUEPROVIDER_H
#define ITOKENVALUEPROVIDER_H

#include <QString>

struct ITokenValueProvider {
    virtual QString tokenValue() = 0;
};

#endif // ITOKENVALUEPROVIDER_H
