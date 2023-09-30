import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property PageStack pageStack
    Component.onCompleted: start()

    function start() {
        var page = instantiatePage("pages/StartPage.qml")
        page.navLogin.connect(login)
        page.navSignup.connect(signup)
        pageStack.push(page)
    }

    function login() {
        console.log("PAM")
    }

    function signup() {
        console.log("PAM")
    }

    function instantiatePage(path) {
        return Qt.createComponent(Qt.resolvedUrl("pages/StartPage.qml")).createObject();
    }
}
