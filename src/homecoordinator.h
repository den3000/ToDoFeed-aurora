#ifndef HOMECOORDINATOR_H
#define HOMECOORDINATOR_H

#include "easy_import.h"

#include <QObject>
#include <QtQuick>

#include "smoozyutils.h"
#include "pagepaths.h"

#include "todolistvm.h"
#include "tododetailsvm.h"
#include "edittodovm.h"

#include "ilogouttokenprovider.h"

class HomeCoordinator : public QObject
{
    Q_OBJECT

    shared_ptr<QQuickItem> pageStackCppWrapper;
    shared_ptr<ILogoutTokenProvider> tokenProvider;

public:
    explicit HomeCoordinator(shared_ptr<QQuickItem> pageStackCppWrapper, shared_ptr<ILogoutTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , pageStackCppWrapper { pageStackCppWrapper }
        , tokenProvider { tokenProvider }
    {};

    ~HomeCoordinator(){};

    void start(bool isReplace = false){
        auto vm = new ToDoListVM();
        QObject::connect(vm, &ToDoListVM::showToDo, this, &HomeCoordinator::showToDo);
        QObject::connect(vm, &ToDoListVM::addToDo, this, &HomeCoordinator::addToDo);
        QObject::connect(vm, &ToDoListVM::showUsersList, this, &HomeCoordinator::showUsersList);
        QObject::connect(vm, &ToDoListVM::showSettings, this, &HomeCoordinator::showSettings);

        if (isReplace) {
            Smoozy::replaceAllWithNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::toDoListPage), Smoozy::wrapInProperties(vm));
        } else {
            Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::toDoListPage), Smoozy::wrapInProperties(vm));
        }
    };

signals:
    void logout();
public slots:
    void restart() { start(true); };

    void showToDo() {
        auto vm = new ToDoDetailsVM();
        QObject::connect(vm, &ToDoDetailsVM::editToDo, this, &HomeCoordinator::editToDo);
        Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::toDoDetailsPage), Smoozy::wrapInProperties(vm));
    };

    void addToDo(IEditToDoDelegate * delegate) { editToDo("", delegate); }

    void editToDo(QString const & toDoId, IEditToDoDelegate * delegate) {
        auto vm = new EditToDoVM(toDoId, delegate);
        QObject::connect(vm, &EditToDoVM::confirmed, this, &HomeCoordinator::confirmed);
        Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::editToDoPage), Smoozy::wrapInProperties(vm));
    };

    void showUsersList() {
        qDebug();
    };

    void showSettings() {
        qDebug();
    };

    void confirmed() {
        qDebug();
        Smoozy::popPage(pageStackCppWrapper.get());
    };

};
#endif // HOMECOORDINATOR_H
