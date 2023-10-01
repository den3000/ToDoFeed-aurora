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
}

#endif // SMOOZYUTILS_H
