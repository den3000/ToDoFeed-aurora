#ifndef SMOOZYUTILS_H
#define SMOOZYUTILS_H

#include <QObject>
#include <QtQuick>
#include <QSettings>

#include <auroraapp.h>

namespace Smoozy
{
    inline QSettings settings(QString const & fileName = "/settings.ini") {
        return QSettings (QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation).append(fileName), QSettings::IniFormat);
    };

    inline QQuickItem * findQuickViewChildByObjectName(QQuickView * quickView, QString const & objectName = "pageStackCppWrapper") {
        return quickView->rootObject()->findChild<QQuickItem *>(objectName);
    }

    inline QQuickItem * findQuickViewPropertyByPropertyName(QQuickView * quickView, const char * propertyName){
        QVariant propertyVariant = quickView->rootObject()->property(propertyName);
        QObject * propertyObject = qvariant_cast<QObject *>(propertyVariant);
        return qobject_cast<QQuickItem *>(propertyObject);
    }

    inline QQmlComponent * createPage(QQuickView * rootView, const char * pageName){
        return new QQmlComponent(
                    rootView->engine(),
                    Aurora::Application::pathTo(pageName),
                    rootView->rootObject()
                    );
    }

    template<typename T>
    inline bool pushPage(QQuickItem * pageStackCppWrapper, QQmlComponent * page, T * vm){
        QMap<QString, QVariant> properties;
        properties["viewModel"] = QVariant::fromValue<T *>(vm);
        return QMetaObject::invokeMethod(
                    pageStackCppWrapper,
                    "push",
                    Q_ARG(QVariant, QVariant::fromValue(page)),
                    Q_ARG(QVariant, QVariant::fromValue(properties))
                    );
    }

    template<typename T>
    inline bool pushNamedPage(QQuickItem * pageStackCppWrapper, QString const & pageName, T * vm){
        QMap<QString, QVariant> properties;
        properties["viewModel"] = QVariant::fromValue<T *>(vm);
        return QMetaObject::invokeMethod(
                    pageStackCppWrapper,
                    "push",
                    Q_ARG(QVariant, QVariant::fromValue(Aurora::Application::pathTo(pageName))),
                    Q_ARG(QVariant, QVariant::fromValue(properties))
                    );
    }

    template<typename T>
    inline bool replaceAllWithNamedPage(QQuickItem * pageStackCppWrapper, QString const & pageName, T * vm){
        QMap<QString, QVariant> properties;
        properties["viewModel"] = QVariant::fromValue<T *>(vm);
        return QMetaObject::invokeMethod(
                    pageStackCppWrapper,
                    "replaceAll",
                    Q_ARG(QVariant, QVariant::fromValue(Aurora::Application::pathTo(pageName))),
                    Q_ARG(QVariant, QVariant::fromValue(properties))
                    );
    }

    inline bool popPage(QQuickItem * pageStackCppWrapper){
        return QMetaObject::invokeMethod(
                    pageStackCppWrapper,
                    "pop"
                    );
    }
}

#endif // SMOOZYUTILS_H
