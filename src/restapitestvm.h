#ifndef RESTAPITESTVM_H
#define RESTAPITESTVM_H

#include <QObject>

class RestApiTestVM : public QObject
{
    Q_OBJECT
public:
    explicit RestApiTestVM(QObject *parent = nullptr);

signals:

};

#endif // RESTAPITESTVM_H
