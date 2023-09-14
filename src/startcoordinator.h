#ifndef STARTCOORDINATOR_H
#define STARTCOORDINATOR_H

#include <QObject>
#include <QtQuick>

#include "startvm.h"
#include "smoozyutils.h"
#include "pagepaths.h"

class StartCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit StartCoordinator(QSharedPointer<QQuickItem> pageStackCppWrapper, QObject *parent = nullptr)
        : QObject(parent)
        , pageStackCppWrapper { pageStackCppWrapper }
    {};

    ~StartCoordinator(){};

    void start(){
        auto vm = new StartVM();
        Smoozy::pushNamedPage(pageStackCppWrapper.data(), Aurora::Application::pathTo(PagePaths::startPage), Smoozy::wrapInProperties(vm));
    };

private:
    QSharedPointer<QQuickView> rootView;
    QSharedPointer<QQuickItem> pageStackCppWrapper;

public slots:
};

#endif // STARTCOORDINATOR_H
