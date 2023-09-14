#ifndef CUSTOMCPPCLASSES_H
#define CUSTOMCPPCLASSES_H

#include "QtQuick"
#include "restapitestvm.h"

namespace CustomCppClasses {
    void registerModuleInQml() {
        qmlRegisterType<RestApiTestVM>("CustomCppClasses.Module", 1, 0, "RestApiTestVM");
    }
}
#endif // CUSTOMCPPCLASSES_H
