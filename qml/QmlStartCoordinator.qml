import QtQuick 2.0
import Sailfish.Silica 1.0

QmlCoordinator {
    signal authorized

    function start(isRestart) {
        var page = instantiatePage("pages/StartPage.qml")
        page.navLogin.connect(login)
        page.navSignup.connect(signup)

        if (isRestart) {
            pageStack.replaceAbove(null, page)
        } else {
            pageStack.push(page)
        }
    }

    function login() {
        console.log("PAM")
        authorized()
    }

    function signup() {
        console.log("PAM")
        authorized()
    }

    function restart() {
        console.log("PAM")
        start(true)
    }
}
