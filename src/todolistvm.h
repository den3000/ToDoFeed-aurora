#ifndef TODOLISTVM_H
#define TODOLISTVM_H

#include <QObject>

#include "todosservice.h"

#include "edittodovm.h"

class ToDoListVM : public QObject, public IEditToDoDelegate
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    shared_ptr<ToDosService> m_service;

public:
    explicit ToDoListVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit ToDoListVM(shared_ptr<ToDosService> service, QObject *parent = nullptr)
        : QObject(parent)
        , m_service{ service }
    { qDebug(); };
    ~ToDoListVM() { qDebug(); }

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
    }

    Q_INVOKABLE void callAddToDo() {
        emit addToDo(this);
    };

signals:
    void showToDo(QString toDoId);
    void addToDo(IEditToDoDelegate * delegate);
    void showUsersList();
    void showSettings();

};

#endif // TODOLISTVM_H
