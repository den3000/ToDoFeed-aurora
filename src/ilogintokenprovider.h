#ifndef ILOGINTOKENPROVIDER_H
#define ILOGINTOKENPROVIDER_H

#include <QString>

struct ILoginTokenProvider {
    virtual void login(QString const & token) = 0;
};

#endif // ILOGINTOKENPROVIDER_H
