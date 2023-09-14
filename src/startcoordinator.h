#ifndef STARTCOORDINATOR_H
#define STARTCOORDINATOR_H

#include <QObject>
#include <QtQuick>

#include "smoozyutils.h"
#include "pagepaths.h"

#include "startvm.h"
#include "loginvm.h"
#include "signupvm.h"

class StartCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit StartCoordinator(QSharedPointer<QQuickItem> pageStackCppWrapper, QObject *parent = nullptr)
        : QObject(parent)
        , pageStackCppWrapper { pageStackCppWrapper }
    {};

    ~StartCoordinator(){};

    void start(){
        auto vm = new StartVM();
        QObject::connect(vm, &StartVM::login, this, &StartCoordinator::goToLogin);
        QObject::connect(vm, &StartVM::signup, this, &StartCoordinator::goSignup);

        Smoozy::pushNamedPage(pageStackCppWrapper.data(), Aurora::Application::pathTo(PagePaths::startPage), Smoozy::wrapInProperties(vm));
    };

private:
    QSharedPointer<QQuickView> rootView;
    QSharedPointer<QQuickItem> pageStackCppWrapper;

public slots:

    void goToLogin() {
        auto vm = new LoginVM();
        QObject::connect(vm, &LoginVM::authorized, this, &StartCoordinator::authDone);

        Smoozy::pushNamedPage(pageStackCppWrapper.data(), Aurora::Application::pathTo(PagePaths::loginPage), Smoozy::wrapInProperties(vm));
    };

    void goSignup() {
        auto vm = new SignupVM();
        QObject::connect(vm, &SignupVM::authorized, this, &StartCoordinator::authDone);

        Smoozy::pushNamedPage(pageStackCppWrapper.data(), Aurora::Application::pathTo(PagePaths::signupPage), Smoozy::wrapInProperties(vm));
    };

    void authDone(QString const & token) {
        qDebug() << "token" << token;
    };
};

#endif // STARTCOORDINATOR_H
