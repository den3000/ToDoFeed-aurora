#ifndef ILOGOUTTOKENPROVIDER_H
#define ILOGOUTTOKENPROVIDER_H

struct ILogoutTokenProvider {
    virtual void logout() = 0;
};

#endif // ILOGOUTTOKENPROVIDER_H
