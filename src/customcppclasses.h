#ifndef CUSTOMCPPCLASSES_H
#define CUSTOMCPPCLASSES_H

#include "QtQuick"
#include "restapitestvm.h"
#include "startvm.h"
#include "loginvm.h"
#include "signupvm.h"
#include "todolistvm.h"
#include "tododetailsvm.h"
#include "edittodovm.h"

namespace CustomCppClasses {
    void registerModuleInQml() {
        qmlRegisterType<RestApiTestVM>("CustomCppClasses.Module", 1, 0, "RestApiTestVM");
        qmlRegisterType<StartVM>("CustomCppClasses.Module", 1, 0, "StartVM");
        qmlRegisterType<LoginVM>("CustomCppClasses.Module", 1, 0, "LoginVM");
        qmlRegisterType<SignupVM>("CustomCppClasses.Module", 1, 0, "SignupVM");
        qmlRegisterType<ToDoListVM>("CustomCppClasses.Module", 1, 0, "ToDoListVM");
        qmlRegisterType<ToDoDetailsVM>("CustomCppClasses.Module", 1, 0, "ToDoDetailsVM");
        qmlRegisterType<EditToDoVM>("CustomCppClasses.Module", 1, 0, "EditToDoVM");
    }
}
#endif // CUSTOMCPPCLASSES_H
