#ifndef HOMECOORDINATOR_H
#define HOMECOORDINATOR_H

#include "smoozyutils.h"
#include "pagepaths.h"

#include "ihomediprovider.h"

class HomeCoordinator : public QObject
{
    Q_OBJECT

    shared_ptr<QQuickItem> m_pageStackCppWrapper;

    shared_ptr<IHomeDiProvider> m_diProvider;

    shared_ptr<ToDosService> m_toDoService;
    shared_ptr<UsersService> m_usersService;
    shared_ptr<ProfileService> m_profileService;
    shared_ptr<ProfileService> lazyProfileService() {
        if(!m_profileService) {
            m_profileService = m_diProvider->profileServiceInstance();
        }
        return m_profileService;
    };

public:
    explicit HomeCoordinator(shared_ptr<QQuickItem> pageStackCppWrapper, shared_ptr<IHomeDiProvider> diProvider, QObject *parent = nullptr)
        : QObject(parent)
        , m_pageStackCppWrapper { pageStackCppWrapper }
        , m_diProvider { diProvider }
        , m_toDoService { m_diProvider->todosServiceInstance() }
        , m_usersService { m_diProvider->usersServiceInstance() }
    { qDebug(); };

    ~HomeCoordinator() { qDebug(); };

    void start(bool isReplace = false){
        auto vm = unique_unwrap(m_diProvider->toDoListVmInstance(m_toDoService));
        QObject::connect(vm, &ToDoListVM::showToDo, this, &HomeCoordinator::showToDo);
        QObject::connect(vm, &ToDoListVM::addToDo, this, &HomeCoordinator::addToDo);
        QObject::connect(vm, &ToDoListVM::showUsersList, this, &HomeCoordinator::showUsersList);
        QObject::connect(vm, &ToDoListVM::showSettings, this, &HomeCoordinator::showSettings);

        if (isReplace) {
            Smoozy::replaceAllWithNamedPage(m_pageStackCppWrapper.get(), PagePaths::toDoListPage, vm);
        } else {
            Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::toDoListPage, vm);
        }
    };

signals:
    void logout();
public slots:
    void restart() { start(true); };

    void showToDo(QString const & toDoId) {
        auto vm = unique_unwrap(m_diProvider->toDoDetailsVmInstance(m_toDoService, toDoId));
        QObject::connect(vm, &ToDoDetailsVM::editToDo, this, &HomeCoordinator::editToDo);
        Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::toDoDetailsPage, vm);
    };

    void addToDo(IEditToDoDelegate * delegate) { editToDo("", delegate); }

    void editToDo(QString const & toDoId, IEditToDoDelegate * delegate) {
        auto vm = unique_unwrap(m_diProvider->editToDoVmInstance(m_toDoService, toDoId, delegate));
        QObject::connect(vm, &EditToDoVM::confirmed, this, &HomeCoordinator::confirmed);
        Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::editToDoPage, vm);
    };

    void showUsersList() {
        auto vm = unique_unwrap(m_diProvider->usersListVmInstance(m_usersService));
        QObject::connect(vm, &UsersListVM::viewUserDetails, this, &HomeCoordinator::showUserDetails);
        Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::usersListPage, vm);
    };

    void showUserDetails(QString const & userId) {
        auto vm = unique_unwrap(m_diProvider->userDetailsVmInstance(m_usersService, userId));
        QObject::connect(vm, &UserDetailsVM::showToDo, this, &HomeCoordinator::showToDo);
        Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::userDetailsPage, vm);
    };

    void showSettings() {
        auto vm = unique_unwrap(m_diProvider->editProfileVmInstance(lazyProfileService()));
        QObject::connect(vm, &EditProfileVM::unauthorized, this, &HomeCoordinator::logout);
        QObject::connect(vm, &EditProfileVM::finished, this, &HomeCoordinator::finishedSettings);
        Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::editProfilePage, vm);
    };

    void finishedSettings() { qDebug(); };

    void confirmed() { Smoozy::popPage(m_pageStackCppWrapper.get()); };
};
#endif // HOMECOORDINATOR_H
