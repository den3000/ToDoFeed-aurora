/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the My Aurora OS Application project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

#include <auroraapp.h>
#include <QtQuick>

#include "pagepaths.h"
#include "customcppclasses.h"

#include "smoozyutils.h"
#include "restapitestvm.h"

#include "startcoordinator.h"
#include "homecoordinator.h"

int main(int argc, char *argv[])
{
    // excluded in .git/info/exclude
    QFile f(":api.endpoint");
    f.open(QIODevice::ReadOnly);
    auto s = QString(f.readAll());

    auto restApi = QScopedPointer(new RestApi(s));

    CustomCppClasses::registerModuleInQml();

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("ToDoFeed"));

    QScopedPointer<QQuickView> rootView(Aurora::Application::createView());
    rootView->setSource(Aurora::Application::pathTo(PagePaths::root));

    auto pageStackCppWrapper = QSharedPointer<QQuickItem>(Smoozy::findQuickViewChildByObjectName(rootView.data(), "pageStackCppWrapper"));
    rootView->show();

    QScopedPointer<StartCoordinator> startCoordinator(new StartCoordinator(pageStackCppWrapper));
    QObject::connect(startCoordinator.data(), &StartCoordinator::authorized, [pageStackCppWrapper](){
        QScopedPointer<HomeCoordinator> homeCoordinator(new HomeCoordinator(pageStackCppWrapper));
        homeCoordinator->start(true);
    });
    startCoordinator->start();

    return application->exec();
}
