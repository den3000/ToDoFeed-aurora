#ifndef EDITPROFILEVM_H
#define EDITPROFILEVM_H

#include <QObject>

#include "easy_import.h"
#include "ilogintokenprovider.h"
#include "startservice.h"

#include "ilogouttokenprovider.h"

class EditProfileVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    shared_ptr<ILoginTokenProvider> m_loginTokenProvider;
    shared_ptr<StartService> m_startService;

    shared_ptr<ILogoutTokenProvider> m_logoutTokenProvider;

    bool isEditProfile = true;
    bool isAdmin = false;
public:
    explicit EditProfileVM(QObject *parent = nullptr) : QObject(parent) { qDebug(); };

    explicit EditProfileVM(shared_ptr<ILoginTokenProvider> tokenProvider, shared_ptr<StartService> service, QObject *parent = nullptr)
        : QObject(parent)
        , m_loginTokenProvider { tokenProvider }
        , m_startService{ service }
        , isEditProfile { false }
    { qDebug(); };

    explicit EditProfileVM(shared_ptr<ILogoutTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , m_logoutTokenProvider { tokenProvider }
        , isAdmin { true }
    { qDebug(); };

    ~EditProfileVM() { qDebug(); }

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
            m_loginTokenProvider->login("signup_token_value");
            emit authorized();
        }
    };

    Q_INVOKABLE void onLogOut() {
        m_logoutTokenProvider->logout();
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
