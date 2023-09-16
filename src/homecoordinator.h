#ifndef HOMECOORDINATOR_H
#define HOMECOORDINATOR_H

#include "easy_import.h"

#include <QObject>
#include <QtQuick>

#include "smoozyutils.h"
#include "pagepaths.h"

#include "ihomediprovider.h"

#include "todolistvm.h"
#include "tododetailsvm.h"
#include "edittodovm.h"
#include "userslistvm.h"
#include "userdetailsvm.h"
#include "editprofilevm.h"

class HomeCoordinator : public QObject
{
    Q_OBJECT

    shared_ptr<QQuickItem> pageStackCppWrapper;
    shared_ptr<IHomeDiProvider> diProvider;

public:
    explicit HomeCoordinator(shared_ptr<QQuickItem> pageStackCppWrapper, shared_ptr<IHomeDiProvider> diProvider, QObject *parent = nullptr)
        : QObject(parent)
        , pageStackCppWrapper { pageStackCppWrapper }
        , diProvider { diProvider }
    { qDebug(); };

    ~HomeCoordinator() { qDebug(); };

    void start(bool isReplace = false){
        auto vm = new ToDoListVM();
        QObject::connect(vm, &ToDoListVM::showToDo, this, &HomeCoordinator::showToDo);
        QObject::connect(vm, &ToDoListVM::addToDo, this, &HomeCoordinator::addToDo);
        QObject::connect(vm, &ToDoListVM::showUsersList, this, &HomeCoordinator::showUsersList);
        QObject::connect(vm, &ToDoListVM::showSettings, this, &HomeCoordinator::showSettings);

        if (isReplace) {
            Smoozy::replaceAllWithNamedPage(pageStackCppWrapper.get(), PagePaths::toDoListPage, vm);
        } else {
            Smoozy::pushNamedPage(pageStackCppWrapper.get(), PagePaths::toDoListPage, vm);
        }
    };

signals:
    void logout();
public slots:
    void restart() { start(true); };

    void showToDo(QString const & toDoId) {
        auto vm = new ToDoDetailsVM(toDoId);
        QObject::connect(vm, &ToDoDetailsVM::editToDo, this, &HomeCoordinator::editToDo);
        Smoozy::pushNamedPage(pageStackCppWrapper.get(), PagePaths::toDoDetailsPage, vm);
    };

    void addToDo(IEditToDoDelegate * delegate) { editToDo("", delegate); }

    void editToDo(QString const & toDoId, IEditToDoDelegate * delegate) {
        auto vm = new EditToDoVM(toDoId, delegate);
        QObject::connect(vm, &EditToDoVM::confirmed, this, &HomeCoordinator::confirmed);
        Smoozy::pushNamedPage(pageStackCppWrapper.get(), PagePaths::editToDoPage, vm);
    };

    void showUsersList() {
        auto vm = new UsersListVM();
        QObject::connect(vm, &UsersListVM::viewUserDetails, this, &HomeCoordinator::showUserDetails);
        Smoozy::pushNamedPage(pageStackCppWrapper.get(), PagePaths::usersListPage, vm);
    };

    void showUserDetails(QString const & userId) {
        auto vm = new UserDetailsVM(userId);
        QObject::connect(vm, &UserDetailsVM::showToDo, this, &HomeCoordinator::showToDo);
        Smoozy::pushNamedPage(pageStackCppWrapper.get(), PagePaths::userDetailsPage, vm);
    };

    void showSettings() {
        auto vm = new EditProfileVM(diProvider->logoutTokenProvider());
        QObject::connect(vm, &EditProfileVM::unauthorized, this, &HomeCoordinator::logout);
        Smoozy::pushNamedPage(pageStackCppWrapper.get(), PagePaths::editProfilePage, vm);
    };

    void confirmed() {
        Smoozy::popPage(pageStackCppWrapper.get());
    };

};
#endif // HOMECOORDINATOR_H
