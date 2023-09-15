#ifndef CUSTOMCPPCLASSES_H
#define CUSTOMCPPCLASSES_H

#include "QtQuick"
#include "restapitestvm.h"
#include "startvm.h"
#include "loginvm.h"
#include "editprofilevm.h"
#include "todolistvm.h"
#include "tododetailsvm.h"
#include "edittodovm.h"
#include "userslistvm.h"
#include "userdetailsvm.h"

namespace CustomCppClasses {
    void registerModuleInQml() {
        qmlRegisterType<RestApiTestVM>("CustomCppClasses.Module", 1, 0, "RestApiTestVM");
        qmlRegisterType<StartVM>("CustomCppClasses.Module", 1, 0, "StartVM");
        qmlRegisterType<LoginVM>("CustomCppClasses.Module", 1, 0, "LoginVM");
        qmlRegisterType<EditProfileVM>("CustomCppClasses.Module", 1, 0, "EditProfileVM");
        qmlRegisterType<ToDoListVM>("CustomCppClasses.Module", 1, 0, "ToDoListVM");
        qmlRegisterType<ToDoDetailsVM>("CustomCppClasses.Module", 1, 0, "ToDoDetailsVM");
        qmlRegisterType<EditToDoVM>("CustomCppClasses.Module", 1, 0, "EditToDoVM");
        qmlRegisterType<UsersListVM>("CustomCppClasses.Module", 1, 0, "UsersListVM");
        qmlRegisterType<UserDetailsVM>("CustomCppClasses.Module", 1, 0, "UserDetailsVM");
    }
}
#endif // CUSTOMCPPCLASSES_H
