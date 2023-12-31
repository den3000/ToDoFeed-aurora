################################################################################
##
## Copyright (C) 2022 ru.auroraos
## 
## This file is part of the My Aurora OS Application project.
##
## Redistribution and use in source and binary forms,
## with or without modification, are permitted provided
## that the following conditions are met:
##
## * Redistributions of source code must retain the above copyright notice,
##   this list of conditions and the following disclaimer.
## * Redistributions in binary form must reproduce the above copyright notice,
##   this list of conditions and the following disclaimer
##   in the documentation and/or other materials provided with the distribution.
## * Neither the name of the copyright holder nor the names of its contributors
##   may be used to endorse or promote products derived from this software
##   without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
## THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
## FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
## IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
## FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
## OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
## LOSS OF USE, DATA, OR PROFITS;
## OR BUSINESS INTERRUPTION)
## HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
## WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
## EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
################################################################################

TARGET = ru.auroraos.ToDoFeed

CONFIG += \
    auroraapp\
    c++1z

PKGCONFIG += \

SOURCES += \
    src/main.cpp \
    src/restapi.cpp \
    src/restapitestvm.cpp \
    src/tododto.cpp \
    src/userdto.cpp

HEADERS += \
    src/addtodo.h \
    src/appdataprovider.h \
    src/customcppclasses.h \
    src/diconsumer.h \
    src/diprovider.h \
    src/easy_import.h \
    src/editprofile.h \
    src/editprofilevm.h \
    src/edittodo.h \
    src/edittodovm.h \
    src/eraseall.h \
    src/getallusers.h \
    src/getprofile.h \
    src/gettododetails.h \
    src/gettodoslist.h \
    src/getuserdetails.h \
    src/ihomediprovider.h \
    src/ilogintokenprovider.h \
    src/ilogouttokenprovider.h \
    src/istartdiprovider.h \
    src/itokenvalueprovider.h \
    src/login.h \
    src/loginvm.h \
    src/pagedestroyedlistener.h \
    src/profileservice.h \
    src/restapi.h \
    src/restapitestvm.h \
    src/restapitypes.h \
    src/signup.h \
    src/smoozyutils.h \
    src/startservice.h \
    src/startvm.h \
    src/tododetailsvm.h \
    src/tododto.h \
    src/todolistvm.h \
    src/todosservice.h \
    src/userdetailsvm.h \
    src/userdto.h \
    src/userslistvm.h \
    src/usersservice.h

DISTFILES += \
    qml/QmlCoordinator.qml \
    qml/QmlHomeCoordinator.qml \
    qml/QmlStartCoordinator.qml \
    qml/items/ToDoItem.qml \
    qml/pages/EditProfilePage.qml \
    qml/pages/EditToDoPage.qml \
    qml/pages/LoginPage.qml \
    qml/pages/UserDetailsPage.qml \
    qml/pages/UsersListPage.qml \
    qml/pages/RestApiTestPage.qml \
    qml/pages/StartPage.qml \
    qml/pages/ToDoDetailsPage.qml \
    qml/pages/ToDoListPage.qml \
    rpm/ru.auroraos.ToDoFeed.spec \
    AUTHORS.md \
    CODE_OF_CONDUCT.md \
    CONTRIBUTING.md \
    LICENSE.BSD-3-CLAUSE.md \
    README.md \

RESOURCES += \
    api.endpoint

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.ToDoFeed.ts \
    translations/ru.auroraos.ToDoFeed-ru.ts \
