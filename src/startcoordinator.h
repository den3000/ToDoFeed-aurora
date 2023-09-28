#ifndef STARTCOORDINATOR_H
#define STARTCOORDINATOR_H

#include "smoozyutils.h"
#include "pagepaths.h"

#include "istartdiprovider.h"

class StartCoordinator : public QObject
{
    Q_OBJECT

    shared_ptr<QQuickItem> m_pageStackCppWrapper;

    shared_ptr<IStartDiProvider> m_diProvider;

    shared_ptr<StartService> m_startService;
    shared_ptr<StartService> lazyStartService() {
        if(!m_startService) {
            m_startService = m_diProvider->startServiceInstance();
        }
        return m_startService;
    };

public:
    explicit StartCoordinator(shared_ptr<QQuickItem> pageStackCppWrapper, shared_ptr<IStartDiProvider> diProvider, QObject *parent = nullptr)
        : QObject(parent)
        , m_pageStackCppWrapper { pageStackCppWrapper }
        , m_diProvider { diProvider }
    { qDebug(); };

    ~StartCoordinator() { qDebug(); };

    void start(bool isReplace = false) {
        auto vm = unique_unwrap(m_diProvider->startVmInstance());

        QObject::connect(vm, &StartVM::login, this, &StartCoordinator::goToLogin);
        QObject::connect(vm, &StartVM::signup, this, &StartCoordinator::goSignup);

        if (isReplace) {
            Smoozy::replaceAllWithNamedPage(m_pageStackCppWrapper.get(), PagePaths::startPage, vm);
        } else {
            Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::startPage, vm);
        }
    };

public slots:
    void goToLogin() {
        auto vm = unique_unwrap(m_diProvider->loginVmInstance(lazyStartService()));
        QObject::connect(vm, &LoginVM::authorized, this, &StartCoordinator::authorized);

        Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::loginPage, vm);
    };

    void goSignup() {
        auto vm = unique_unwrap(m_diProvider->editProfileInstance(lazyStartService()));
        QObject::connect(vm, &EditProfileVM::authorized, this, &StartCoordinator::authorized);

        Smoozy::pushNamedPage(m_pageStackCppWrapper.get(), PagePaths::editProfilePage, vm);
    };

signals:
    void authorized();
public slots:
    void restart() { start(true); };
};

#endif // STARTCOORDINATOR_H
