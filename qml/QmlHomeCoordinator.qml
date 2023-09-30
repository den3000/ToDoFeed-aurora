import QtQuick 2.0
import Sailfish.Silica 1.0

QmlCoordinator {
    signal unauthorized

    function start(isRestart) {
        var vm = diProvider.editProfileVmInstance()
        vm.unauthorized.connect(unauthorized)
        var path = "pages/EditProfilePage.qml"

        if (isRestart) {
            replaceAllPagesWithPageAndVm(path, vm)
        } else {
            pushPageWithVm(path, vm)
        }
    }

    function restart() {
        start(true)
    }
}
