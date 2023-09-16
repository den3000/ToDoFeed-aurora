#ifndef STARTCOORDINATOR_H
#define STARTCOORDINATOR_H

#include "easy_import.h"

#include <QObject>
#include <QtQuick>

#include "smoozyutils.h"
#include "pagepaths.h"

#include "startvm.h"
#include "loginvm.h"
#include "editprofilevm.h"

#include "ilogintokenprovider.h"
#include "istartdiprovider.h"

class StartCoordinator : public QObject
{
    Q_OBJECT

    shared_ptr<QQuickItem> pageStackCppWrapper;
    shared_ptr<IStartDiProvider> diProvider;

public:
    explicit StartCoordinator(shared_ptr<QQuickItem> pageStackCppWrapper, shared_ptr<IStartDiProvider> diProvider, QObject *parent = nullptr)
        : QObject(parent)
        , pageStackCppWrapper { pageStackCppWrapper }
        , diProvider { diProvider }
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
        auto vm = new LoginVM(diProvider->loginTokenProvider());
        QObject::connect(vm, &LoginVM::authorized, this, &StartCoordinator::authDone);

        Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::loginPage), Smoozy::wrapInProperties(vm));
    };

    void goSignup() {
        auto vm = new EditProfileVM(diProvider->loginTokenProvider());
        QObject::connect(vm, &EditProfileVM::authorized, this, &StartCoordinator::authDone);

        Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::editProfilePage), Smoozy::wrapInProperties(vm));
    };

    void authDone() { emit authorized(); };

signals:
    void authorized();
public slots:
    void restart() { start(true); };
};

#endif // STARTCOORDINATOR_H
