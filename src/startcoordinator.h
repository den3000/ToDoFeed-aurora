#ifndef STARTCOORDINATOR_H
#define STARTCOORDINATOR_H

#include "easy_import.h"

#include <QObject>
#include <QtQuick>

#include "smoozyutils.h"
#include "pagepaths.h"

#include "startvm.h"
#include "loginvm.h"
#include "signupvm.h"

#include "ilogintokenprovider.h"

class StartCoordinator : public QObject
{
    Q_OBJECT

    shared_ptr<QQuickItem> pageStackCppWrapper;
    shared_ptr<ILoginTokenProvider> tokenProvider;

public:
    explicit StartCoordinator(shared_ptr<QQuickItem> pageStackCppWrapper, shared_ptr<ILoginTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , pageStackCppWrapper { pageStackCppWrapper }
        , tokenProvider { tokenProvider }
    {};

    ~StartCoordinator(){};

    void start(bool isReplace = false){
        auto vm = new StartVM();
        QObject::connect(vm, &StartVM::login, this, &StartCoordinator::goToLogin);
        QObject::connect(vm, &StartVM::signup, this, &StartCoordinator::goSignup);

        if (isReplace) {
            Smoozy::replaceAllWithNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::startPage), Smoozy::wrapInProperties(vm));
        } else {
            Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::startPage), Smoozy::wrapInProperties(vm));
        }
    };

public slots:
    void goToLogin() {
        auto vm = new LoginVM();
        QObject::connect(vm, &LoginVM::authorized, this, &StartCoordinator::authDone);

        Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::loginPage), Smoozy::wrapInProperties(vm));
    };

    void goSignup() {
        auto vm = new SignupVM();
        QObject::connect(vm, &SignupVM::authorized, this, &StartCoordinator::authDone);

        Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::signupPage), Smoozy::wrapInProperties(vm));
    };

    void authDone(QString const & token) {
        qDebug() << "token" << token;
        emit authorized();
    };

signals:
    void authorized();
public slots:
    void restart() { start(true); };
};

#endif // STARTCOORDINATOR_H
