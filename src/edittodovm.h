#ifndef EDITTODOVM_H
#define EDITTODOVM_H

#include <QObject>

#include "todosservice.h"

class EditToDoVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
signals:
    void toDoDetailsLoaded(
        QString title,
        QString description,
        int statusIdx,
        int visibilityIdx
    );
    void finishedEditing();

private:
    shared_ptr<ToDosService> m_service;
    QString m_toDoId;

public:
    explicit EditToDoVM(QObject *parent = nullptr): QObject(parent) { qDebug(); };
    explicit EditToDoVM(shared_ptr<ToDosService> service, QString const & toDoId, QObject *parent = nullptr)
        : QObject(parent)
        , m_service{ service }
        , m_toDoId { toDoId }
    { qDebug(); };
    ~EditToDoVM() { qDebug(); }

    Q_INVOKABLE void start() { loadToDoDetails(); }

    Q_INVOKABLE bool isEdit() { return !m_toDoId.isEmpty(); }

    Q_INVOKABLE void confirm(
        QString const & title,
        QString const & details,
        int statusIdx,
        int visibilityIdx
    ) {
        auto status = ToDoDto::statusFromIdx(statusIdx);
        auto visibility = ToDoDto::visibilityFromIdx(visibilityIdx);

        if (!status.has_value() || !visibility.has_value()) { return; }

        if(m_toDoId.isEmpty()) {
            addToDo(title, details, status.value(), visibility.value());
        } else {
            editToDo(title, details, status.value(), visibility.value());
        }
    };

private:
    void loadToDoDetails() {
        if (m_toDoId.isEmpty()) { return; }

        resOrErr(m_service->getToDoDetails(m_toDoId), this,
        [this](auto * response) {
            qDebug() << "get todo details";
            qDebug() << "todo" << response->toDo;
            emit toDoDetailsLoaded(
                response->toDo.title,
                response->toDo.description,
                response->toDo.statusIdx(),
                response->toDo.visibilityIdx()
            );
        }, [](auto * error){
            Q_UNUSED(error)
        });
    };

    void addToDo(QString const & title,
                 QString const & details,
                 ToDoDto::Status status,
                 ToDoDto::Visibility visibility){
        resOrErr(m_service->addToDo(title, details, status, visibility), this,
        [this](auto * response){
            qDebug() << "add todo";
            qDebug() << "todo\n" << response->toDo << "\n";
            emit finishedEditing();
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
            emit finishedEditing();
        }, [](auto * error){
            Q_UNUSED(error)
        });
    }
};


#endif // EDITTODOVM_H
