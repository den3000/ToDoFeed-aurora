#ifndef EDITTODOVM_H
#define EDITTODOVM_H

#include <QObject>

#include "todosservice.h"

struct IEditToDoDelegate {
    virtual void onFinished(QString const & toDoId) = 0;
};

class EditToDoVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

signals:
    void confirmed();

private:
    shared_ptr<ToDosService> m_service;
    QString m_toDoId;
    IEditToDoDelegate * m_delegate;

public:
    explicit EditToDoVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit EditToDoVM(shared_ptr<ToDosService> service, QString const & toDoId, IEditToDoDelegate * delegate, QObject *parent = nullptr)
        : QObject(parent)
        , m_service{ service }
        , m_toDoId { toDoId }
        , m_delegate { delegate }
    { qDebug(); };
    ~EditToDoVM() { qDebug(); }

    Q_INVOKABLE bool isEdit() { return !m_toDoId.isEmpty(); }

    Q_INVOKABLE QString title() { return "title " + m_toDoId; }
    Q_INVOKABLE QString details() { return "details " + m_toDoId; }
    Q_INVOKABLE QString status() { return "status " + m_toDoId; }
    Q_INVOKABLE QString visibility() { return "visibility " + m_toDoId; }

    Q_INVOKABLE void confirm(
        QString const & title,
        QString const & details,
        int statusIdx,
        int visibilityIdx
    ) {
        ToDoDto::Status status;
        switch(statusIdx) {
            case 1: status = ToDoDto::Status::Todo; break;
            case 2: status = ToDoDto::Status::InProgress; break;
            case 3: status = ToDoDto::Status::Done; break;
            default: status = ToDoDto::Status::Todo; break;
        }

        ToDoDto::Visibility visibility;
        switch(visibilityIdx) {
            case 1: visibility = ToDoDto::Visibility::Own; break;
            case 2: visibility = ToDoDto::Visibility::ForAll; break;
            default: visibility = ToDoDto::Visibility::Own; break;
        }

        if(m_toDoId.isEmpty()) {
            addToDo(title, details, status, visibility);
        } else {
            editToDo(title, details, status, visibility);
        }

        

    };
private:
    void addToDo(QString const & title,
                 QString const & details,
                 ToDoDto::Status status,
                 ToDoDto::Visibility visibility){
        resOrErr(m_service->addToDo(title, details, status, visibility), this,
        [this](auto * response){
            qDebug() << "add todo";
            qDebug() << "todo\n" << response->toDo << "\n";
            m_delegate->onFinished(m_toDoId);
            emit confirmed();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }

    void editToDo(QString const & title,
                  QString const & details,
                  ToDoDto::Status status,
                  ToDoDto::Visibility visibility){
        resOrErr(m_service->editToDo(m_toDoId, title, details, status, visibility), this,
        [this](auto * response){
            qDebug() << "edit todo";
            qDebug() << "todo\n" << response->toDo << "\n";
            m_delegate->onFinished(m_toDoId);
            emit confirmed();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};


#endif // EDITTODOVM_H
