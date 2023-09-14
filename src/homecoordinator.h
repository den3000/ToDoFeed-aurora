#ifndef HOMECOORDINATOR_H
#define HOMECOORDINATOR_H

#include <QObject>
#include <QtQuick>

#include "smoozyutils.h"
#include "pagepaths.h"

#include "homevm.h"

class HomeCoordinator : public QObject
{
    Q_OBJECT

    QSharedPointer<QQuickItem> pageStackCppWrapper;

public:
    explicit HomeCoordinator(QSharedPointer<QQuickItem> pageStackCppWrapper, QObject *parent = nullptr)
        : QObject(parent)
        , pageStackCppWrapper { pageStackCppWrapper }
    {};

    ~HomeCoordinator(){};

    void start(bool isReplace = false){
        auto vm = new HomeVM();
        QObject::connect(vm, &HomeVM::logout, this, &HomeCoordinator::logout);

        if (isReplace) {
            Smoozy::replaceAllWithNamedPage(pageStackCppWrapper.data(), Aurora::Application::pathTo(PagePaths::homePage), Smoozy::wrapInProperties(vm));
        } else {
            Smoozy::pushNamedPage(pageStackCppWrapper.data(), Aurora::Application::pathTo(PagePaths::homePage), Smoozy::wrapInProperties(vm));
        }
    };

signals:
    void logout();
public slots:
    void restart() { start(true); };

};
#endif // HOMECOORDINATOR_H
