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
    shared_ptr<ToDosService> m_service;

public:
    explicit ToDoListVM(QObject *parent = nullptr): QObject(parent) { qDebug(); }
    explicit ToDoListVM(shared_ptr<ToDosService> service, QObject *parent = nullptr)
        : QObject(parent)
        , m_service{ service }
    { qDebug(); }
    ~ToDoListVM() { qDebug(); }

    Q_INVOKABLE void start() {
        resOrErr(m_service->getAllToDos(), this,
        [](auto * response) {
            qDebug() << "get my todos";
            for(ToDoDto const & toDo : response->todos) {
                qDebug() << "todo\n" << toDo << "\n";
            }
        }, [](auto * error){
            switch (*error) {
            case RestError::NetworkError: qDebug() << "NetworkError"; break;
            case RestError::SslError: qDebug() << "SslError"; break;
            case RestError::NullResponse: qDebug() << "NullResponse"; break;
            case RestError::EmptyJsonResponse: qDebug() << "EmptyJsonResponse"; break;
            case RestError::JsonParsingError: qDebug() << "JsonParsingError"; break;
            }
        });
    }

    Q_INVOKABLE void callAddToDo() {
        emit addToDo(this);
    }

    // IEditToDoDelegate interface
    void onFinished(const QString &toDoId) override {
        Q_UNUSED(toDoId)
        qDebug();
    }
};

#endif // TODOLISTVM_H
