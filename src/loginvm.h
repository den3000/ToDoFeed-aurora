#ifndef LOGINVM_H
#define LOGINVM_H

#include <QObject>

#include "easy_import.h"
#include "ilogintokenprovider.h"

class LoginVM : public QObject
{
    Q_OBJECT
    shared_ptr<ILoginTokenProvider> tokenProvider;

public:
    explicit LoginVM(QObject *parent = nullptr): QObject(parent) { };
    explicit LoginVM(shared_ptr<ILoginTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , tokenProvider { tokenProvider }
    { };

    Q_INVOKABLE void loginPressed(QString const & password) {
        qDebug () << "password: " << password;
        tokenProvider.get()->login("login_token_value");
        emit authorized();
    };

signals:
    void authorized();
};

#endif // LOGINVM_H
