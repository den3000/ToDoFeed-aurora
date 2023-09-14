#ifndef HOMECOORDINATOR_H
#define HOMECOORDINATOR_H

#include "easy_import.h"

#include <QObject>
#include <QtQuick>

#include "smoozyutils.h"
#include "pagepaths.h"

#include "homevm.h"

#include "ilogouttokenprovider.h"

class HomeCoordinator : public QObject
{
    Q_OBJECT

    shared_ptr<QQuickItem> pageStackCppWrapper;
    shared_ptr<ILogoutTokenProvider> tokenProvider;

public:
    explicit HomeCoordinator(shared_ptr<QQuickItem> pageStackCppWrapper, shared_ptr<ILogoutTokenProvider> tokenProvider, QObject *parent = nullptr)
        : QObject(parent)
        , pageStackCppWrapper { pageStackCppWrapper }
        , tokenProvider { tokenProvider }
    {};

    ~HomeCoordinator(){};

    void start(bool isReplace = false){
        auto vm = new HomeVM(tokenProvider);
        QObject::connect(vm, &HomeVM::logout, this, &HomeCoordinator::logout);

        if (isReplace) {
            Smoozy::replaceAllWithNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::homePage), Smoozy::wrapInProperties(vm));
        } else {
            Smoozy::pushNamedPage(pageStackCppWrapper.get(), Aurora::Application::pathTo(PagePaths::homePage), Smoozy::wrapInProperties(vm));
        }
    };

signals:
    void logout();
public slots:
    void restart() { start(true); };

};
#endif // HOMECOORDINATOR_H
