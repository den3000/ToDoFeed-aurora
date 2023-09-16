#ifndef LOGINVM_H
#define LOGINVM_H

#include <QObject>

#include "easy_import.h"

#include "ilogintokenprovider.h"
#include "startservice.h"

class LoginVM : public QObject
{
    Q_OBJECT
    shared_ptr<ILoginTokenProvider> m_tokenProvider;
    shared_ptr<StartService> m_service;

public:
    explicit LoginVM(QObject *parent = nullptr): QObject(parent) {  };
    explicit LoginVM(shared_ptr<ILoginTokenProvider> tokenProvider, shared_ptr<StartService> service, QObject *parent = nullptr)
        : QObject(parent)
        , m_tokenProvider { tokenProvider }
        , m_service { service }
    {  };

    ~LoginVM(){ qDebug () << "destructor"; };

    Q_INVOKABLE void loginPressed(QString const & password) {
        qDebug () << "password: " << password;
        m_tokenProvider->login("login_token_value");
        emit authorized();
    };

signals:
    void authorized();
};

#endif // LOGINVM_H
