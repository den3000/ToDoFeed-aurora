#ifndef IHOMEDIPROVIDER_H
#define IHOMEDIPROVIDER_H

#include "easy_import.h"

#include "itokenvalueprovider.h"
#include "ilogouttokenprovider.h"
#include "restapi.h"

#include "usersservice.h"
#include "todosservice.h"
#include "profileservice.h"

#include "todolistvm.h"
#include "tododetailsvm.h"
#include "edittodovm.h"
#include "userslistvm.h"
#include "userdetailsvm.h"
#include "editprofilevm.h"

struct IHomeDiProvider {
    // provide
    unique_ptr<ToDosService> todosServiceInstance()
        { return make_unique<ToDosService>(restApi(), tokenValueProvider()); }

    unique_ptr<UsersService> usersServiceInstance()
        { return make_unique<UsersService>(restApi(), tokenValueProvider()); }

    unique_ptr<ProfileService> profileServiceInstance()
        { return make_unique<ProfileService>(restApi(), tokenValueProvider()); }

    unique_ptr<ToDoListVM> toDoListVmInstance(shared_ptr<ToDosService> service)
        { return make_unique<ToDoListVM>(service); }

    unique_ptr<ToDoDetailsVM> toDoDetailsVmInstance(shared_ptr<ToDosService> service, QString const & todoId)
        { return make_unique<ToDoDetailsVM>(service, todoId); }

    unique_ptr<EditToDoVM> editToDoVmInstance(shared_ptr<ToDosService> service, QString const & toDoId)
        { return make_unique<EditToDoVM>(service, toDoId); }

    unique_ptr<UsersListVM> usersListVmInstance(shared_ptr<UsersService> service)
        { return make_unique<UsersListVM>(service); }

    unique_ptr<UserDetailsVM> userDetailsVmInstance(shared_ptr<UsersService> userService, shared_ptr<ToDosService> toDosService, QString const & userId)
        { return make_unique<UserDetailsVM>(userService, toDosService, userId); }

    unique_ptr<EditProfileVM> editProfileVmInstance(shared_ptr<ProfileService> service)
        { return make_unique<EditProfileVM>(logoutTokenProvider(), service); }

    // require
protected:
    virtual shared_ptr<RestApi> restApi() = 0;
    virtual shared_ptr<ILogoutTokenProvider> logoutTokenProvider() = 0;
    virtual shared_ptr<ITokenValueProvider> tokenValueProvider() = 0;
};

#endif // IHOMEDIPROVIDER_H
