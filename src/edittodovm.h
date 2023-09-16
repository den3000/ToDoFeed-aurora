#ifndef EDITTODOVM_H
#define EDITTODOVM_H

#include <QObject>

#include "easy_import.h"

struct IEditToDoDelegate {
    virtual void onFinished(QString const & toDoId) = 0;
};

class EditToDoVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    QString toDoId;
    IEditToDoDelegate * delegate;

public:
    explicit EditToDoVM(QObject *parent = nullptr): QObject(parent) { };
    explicit EditToDoVM(QString const & toDoId, IEditToDoDelegate * delegate, QObject *parent = nullptr)
        : QObject(parent)
        , toDoId { toDoId }
        , delegate { delegate }
    { };

    Q_INVOKABLE bool isEdit() { return !toDoId.isEmpty(); }

    Q_INVOKABLE QString title() { return "title " + toDoId; }
    Q_INVOKABLE QString details() { return "details " + toDoId; }
    Q_INVOKABLE QString status() { return "status " + toDoId; }
    Q_INVOKABLE QString visibility() { return "visibility " + toDoId; }

    Q_INVOKABLE void confirm() {
        delegate->onFinished(toDoId);
        emit confirmed();
    };

signals:
    void confirmed();
};


#endif // EDITTODOVM_H
