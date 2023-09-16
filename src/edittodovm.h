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

    Q_INVOKABLE void confirm() {
        m_delegate->onFinished(m_toDoId);
        emit confirmed();
    };

signals:
    void confirmed();
};


#endif // EDITTODOVM_H
