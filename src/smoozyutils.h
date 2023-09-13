#ifndef SMOOZYUTILS_H
#define SMOOZYUTILS_H

#include <QObject>
#include <QtQuick>

#include <auroraapp.h>

namespace Smoozy
{
    inline QQuickItem * findQuickViewChildByObjectName(QQuickView * quickView, const char * objectName) {
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

    inline bool pushPage(QQuickItem * qmlCoordinatorInstance, QQmlComponent * page, QMap<QString, QVariant> properties){
        return QMetaObject::invokeMethod(
                    qmlCoordinatorInstance,
                    "push",
                    Q_ARG(QVariant, QVariant::fromValue(page)),
                    Q_ARG(QVariant, QVariant::fromValue(properties))
                    );
    }

    inline bool pushNamedPage(QQuickItem * qmlCoordinatorInstance, QUrl pageName, QMap<QString, QVariant> properties){
        return QMetaObject::invokeMethod(
                    qmlCoordinatorInstance,
                    "push",
                    Q_ARG(QVariant, QVariant::fromValue(pageName)),
                    Q_ARG(QVariant, QVariant::fromValue(properties))
                    );
    }

    template<typename T>
    inline QMap<QString, QVariant> wrapInProperties(T * vm){
        QMap<QString, QVariant> properties;
        properties["viewModel"] = QVariant::fromValue<T *>(vm);
        return properties;
    }
}

#endif // SMOOZYUTILS_H
