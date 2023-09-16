#ifndef LOGINVM_H
#define LOGINVM_H

#include <QObject>

#include "easy_import.h"

#include "ilogintokenprovider.h"
#include "startservice.h"

class LoginVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    shared_ptr<ILoginTokenProvider> m_tokenProvider;
    shared_ptr<StartService> m_service;

public:
    explicit LoginVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit LoginVM(shared_ptr<ILoginTokenProvider> tokenProvider, shared_ptr<StartService> service, QObject *parent = nullptr)
        : QObject(parent)
        , m_tokenProvider { tokenProvider }
        , m_service { service }
    { qDebug(); };

    ~LoginVM() { qDebug(); };

    Q_INVOKABLE void loginPressed(QString const & password) {
        resOrErr(m_service->login(password), this, [this](auto * response){
            qDebug() << "log in";
            qDebug() << "user: token" << response->token;
            qDebug() << "user\n" << response->user;

            m_tokenProvider->login("login_token_value");
            emit authorized();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    };

signals:
    void authorized();
};

#endif // LOGINVM_H
