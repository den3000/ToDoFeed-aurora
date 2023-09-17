#ifndef TODODETAILSVM_H
#define TODODETAILSVM_H

#include <QObject>

#include "todosservice.h"

#include "edittodovm.h"

class ToDoDetailsVM : public QObject, public IEditToDoDelegate
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void editToDo(QString const & toDoId, IEditToDoDelegate * delegate);
    void toDoDetailsLoaded(
        QString title,
        QString description,
        QString status,
        QString visibility,
        bool isEditable
    );

private:

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

    Q_INVOKABLE void start() {
        resOrErr(m_service->getToDoDetails(m_toDoId), this,
        [this](auto * response) {
            qDebug() << "get todo details";
            qDebug() << "todo" << response->toDo;
            emit toDoDetailsLoaded(
                response->toDo.title,
                response->toDo.description,
                "_status_",
                "_visibility_",
                response->isEditable
            );
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    Q_INVOKABLE void onEditToDo() {
        emit editToDo(m_toDoId, this);
    };

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
    }
};

#endif // TODODETAILSVM_H
