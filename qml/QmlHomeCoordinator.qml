import QtQuick 2.0
import Sailfish.Silica 1.0

QmlCoordinator {
    signal unauthorized

    function start(isRestart) {
        var page = instantiatePage("pages/EditProfilePage.qml")
        page.navLogout.connect(unauthorized)

        if (isRestart) {
            pageStack.replaceAbove(null, page)
        } else {
            pageStack.push(page)
        }
    }

    function restart() {
        start(true)
    }
}
