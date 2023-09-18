#ifndef EDITPROFILEVM_H
#define EDITPROFILEVM_H

#include <QObject>

#include "easy_import.h"
#include "ilogintokenprovider.h"
#include "startservice.h"

#include "ilogouttokenprovider.h"
#include "profileservice.h"

class EditProfileVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void authorized();
    void unauthorized();
    void finished();
    void profileLoaded(
        bool isEdit,
        bool isAdmin,
        QString firstName,
        QString lastName,
        QString about
    );

private:
    shared_ptr<ILoginTokenProvider> m_loginTokenProvider;
    shared_ptr<StartService> m_startService;

    shared_ptr<ILogoutTokenProvider> m_logoutTokenProvider;
    shared_ptr<ProfileService> m_profileService;

    bool isEditProfile = true;
    bool isAdmin = false;

public:
    explicit EditProfileVM(QObject *parent = nullptr) : QObject(parent) { qDebug(); }
    explicit EditProfileVM(
            shared_ptr<ILoginTokenProvider> tokenProvider,
            shared_ptr<StartService> service,
            QObject *parent = nullptr
    )
        : QObject(parent)
        , m_loginTokenProvider { tokenProvider }
        , m_startService { service }
        , isEditProfile { false }
    { qDebug(); }

    explicit EditProfileVM(
            shared_ptr<ILogoutTokenProvider> tokenProvider,
            shared_ptr<ProfileService> service,
            QObject *parent = nullptr
    )
        : QObject(parent)
        , m_logoutTokenProvider { tokenProvider }
        , m_profileService { service }
    { qDebug(); }

    ~EditProfileVM() { emit finished(); qDebug(); }

    Q_INVOKABLE void start() {
        if (isEditProfile) {
            loadProfile();
        } else {
            emit profileLoaded(isEditProfile, isAdmin, "", "", "");
        }
    }

    Q_INVOKABLE void onConfirm(
            QString const & password,
            QString const & firstName,
            QString const & lastName,
            QString const & about
    ) {
        if (isEditProfile) {
            update(firstName, lastName, about);
        } else {
            signup(password, firstName, lastName, about);
        }
    }

    Q_INVOKABLE void onLogOut() {
        m_logoutTokenProvider->logout();
        emit unauthorized();
    }

    Q_INVOKABLE void onEraseAll() {
        resOrErr(m_profileService->eraseAll(), this,
        [this](auto *) {
            m_logoutTokenProvider->logout();
            emit unauthorized();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

private:
    void signup(
               QString const & password,
               QString const & firstName,
               QString const & lastName,
               QString const & about
    ) {
        resOrErr(m_startService->signup(password, firstName, lastName, about), this,
        [this](auto * response) {
            m_loginTokenProvider->login(response->token);
            emit authorized();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void update(
               QString const & firstName,
               QString const & lastName,
               QString const & about
    ) {
        resOrErr(m_profileService->updateProfile(firstName, lastName, about), this,
        [this](auto * response) {
            emit profileLoaded(
                isEditProfile,
                isAdmin,
                response->user.firstName,
                response->user.lastName,
                response->user.about
            );
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void loadProfile() {
        resOrErr(m_profileService->getProfile(), this,
        [this](auto * response) {
            isAdmin = response->isAdmin;
            emit profileLoaded(
                isEditProfile,
                isAdmin,
                response->user.firstName,
                response->user.lastName,
                response->user.about
            );
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};

#endif // EDITPROFILEVM_H
