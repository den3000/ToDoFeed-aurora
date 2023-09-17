#ifndef TODOLISTVM_H
#define TODOLISTVM_H

#include <QObject>

#include "todosservice.h"

#include "edittodovm.h"

class ToDoListVM : public QObject, public IEditToDoDelegate
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void showToDo(QString toDoId);
    void addToDo(IEditToDoDelegate * delegate);
    void showUsersList();
    void showSettings();

private:
    bool isOwn = true;
    shared_ptr<ToDosService> m_service;

public:
    explicit ToDoListVM(QObject *parent = nullptr): QObject(parent) { qDebug(); }
    explicit ToDoListVM(shared_ptr<ToDosService> service, QObject *parent = nullptr)
        : QObject(parent)
        , m_service{ service }
    { qDebug(); }
    ~ToDoListVM() { qDebug(); }

    Q_INVOKABLE void start() {
        if (isOwn) {
            loadOwnToDos();
        } else {
            loadAllToDos();
        }
    }

    Q_INVOKABLE void callAddToDo() { emit addToDo(this); }

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
        start();
    }

private:
    void loadOwnToDos() {
        resOrErr(m_service->getMyToDos(), this,
        [](auto * response) {
            qDebug() << "get my todos";
            for(ToDoDto const & toDo : response->todos) {
                qDebug() << "todo\n" << toDo << "\n";
            }
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void loadAllToDos() {
        resOrErr(m_service->getAllToDos(), this,
        [](auto * response) {
            qDebug() << "get all todos";
            for(ToDoDto const & toDo : response->todos) {
                qDebug() << "todo\n" << toDo << "\n";
            }
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};

#endif // TODOLISTVM_H
