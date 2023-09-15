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
    bool isAdmin = false;
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
        , isAdmin { true }
    { };

    Q_INVOKABLE bool edit() { return isEditProfile; }

    Q_INVOKABLE bool admin() { return isAdmin; }

    Q_INVOKABLE void onConfirm(
            QString const & password,
            QString const & firstName,
            QString const & lastName,
            QString const & about
    ) {
        if (isEditProfile) {
            qDebug() << "password: " << password;
            qDebug() << "firstName: " << firstName;
            qDebug() << "lastName: " << lastName;
            qDebug() << "about: " << about;
        } else {
            qDebug() << "firstName: " << firstName;
            qDebug() << "lastName: " << lastName;
            qDebug() << "about: " << about;
            loginTokenProvider.get()->login("signup_token_value");
            emit authorized();
        }
    };

    Q_INVOKABLE void onLogOut() {
        logoutTokenProvider.get()->logout();
        emit unauthorized();
    };

    Q_INVOKABLE void onEraseAll() {
        qDebug();
    };

signals:
    void authorized();
    void unauthorized();
};

#endif // EDITPROFILEVM_H
