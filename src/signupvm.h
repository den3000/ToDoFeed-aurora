#ifndef SIGNUPVM_H
#define SIGNUPVM_H

#include <QObject>

class SignupVM : public QObject
{
    Q_OBJECT

public:
    explicit SignupVM(QObject *parent = nullptr): QObject(parent) { };

    Q_INVOKABLE void signupPressed() { emit authorized("signup_token_value"); };

signals:
    void authorized(QString const & token);
};

#endif // SIGNUPVM_H
