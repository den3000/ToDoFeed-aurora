#ifndef EDITPROFILEVM_H
#define EDITPROFILEVM_H

#include <QObject>

#include "easy_import.h"
#include "ilogintokenprovider.h"
#include "ilogouttokenprovider.h"

class EditProfileVM : public QObject
{
    Q_OBJECT
    shared_ptr<ILoginTokenProvider> loginTokenProvider;
    shared_ptr<ILogoutTokenProvider> logoutTokenProvider;
    bool isEditProfile = true;
public:
    explicit EditProfileVM(QObject *parent = nullptr): QObject(parent) { };

    explicit EditProfileVM(shared_ptr<ILoginTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , loginTokenProvider { tokenProvider }
        , isEditProfile { false }
    { };

    explicit EditProfileVM(shared_ptr<ILogoutTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , logoutTokenProvider { tokenProvider }
    { };

    Q_INVOKABLE bool signup() { return !isEditProfile; }

    Q_INVOKABLE void confirmPressed() {
        if (isEditProfile) {
            logoutTokenProvider.get()->logout();
            emit unauthorized();
        } else {
            loginTokenProvider.get()->login("signup_token_value");
            emit authorized();
        }
    };

signals:
    void authorized();
    void unauthorized();
};

#endif // EDITPROFILEVM_H
