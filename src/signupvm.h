#ifndef SIGNUPVM_H
#define SIGNUPVM_H

#include <QObject>

#include "easy_import.h"
#include "ilogintokenprovider.h"

class SignupVM : public QObject
{
    Q_OBJECT
    shared_ptr<ILoginTokenProvider> tokenProvider;

public:
    explicit SignupVM(QObject *parent = nullptr): QObject(parent) { };
    explicit SignupVM(shared_ptr<ILoginTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , tokenProvider { tokenProvider }
    { };

    Q_INVOKABLE void signupPressed() {
        tokenProvider.get()->login("signup_token_value");
        emit authorized();
    };

signals:
    void authorized();
};

#endif // SIGNUPVM_H
