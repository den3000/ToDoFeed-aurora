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

    Q_INVOKABLE void confirm() {
        delegate->onFinished(toDoId);
        emit confirmed();
    };

signals:
    void confirmed();
};


#endif // EDITTODOVM_H
