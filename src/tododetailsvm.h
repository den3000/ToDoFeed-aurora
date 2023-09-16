#ifndef TODODETAILSVM_H
#define TODODETAILSVM_H

#include <QObject>

#include "todosservice.h"

#include "edittodovm.h"

class ToDoDetailsVM : public QObject, public IEditToDoDelegate
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    shared_ptr<ToDosService> m_service;

    QString m_toDoId;

public:
    explicit ToDoDetailsVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit ToDoDetailsVM(shared_ptr<ToDosService> service, QString const & toDoId, QObject *parent = nullptr)
        : QObject(parent)
        , m_service { service }
        , m_toDoId { toDoId }
    { qDebug(); };
    ~ToDoDetailsVM() { qDebug(); }

    Q_INVOKABLE QString title() { return "title" + m_toDoId; }
    Q_INVOKABLE QString details() { return "details " + m_toDoId; }
    Q_INVOKABLE QString status() { return "status " + m_toDoId; }
    Q_INVOKABLE QString visibility() { return "visibility " + m_toDoId; }

    Q_INVOKABLE void onEditToDo() {
        emit editToDo(m_toDoId, this);
    };

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
    }
signals:
    void editToDo(QString const & toDoId, IEditToDoDelegate * delegate);
};

#endif // TODODETAILSVM_H
