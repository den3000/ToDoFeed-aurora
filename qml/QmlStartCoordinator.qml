import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

QmlCoordinator {
    signal authorized

    function start(isRestart) {
        var vm = diProvider.startVmInstance()
        vm.login.connect(login)
        vm.signup.connect(signup)
        var path = "pages/StartPage.qml"

        if (isRestart) {
            replaceAllPagesWithPageAndVm(path, vm)
        } else {
            pushPageWithVm(path, vm)
        }
    }

    function login() {
        var vm = diProvider.loginVmInstance()
        vm.authorized.connect(authorized)
        var path = "pages/LoginPage.qml"
        pushPageWithVm(path, vm)
    }

    function signup() {
        var vm = diProvider.signupVmInstance()
        vm.authorized.connect(authorized)
        var path = "pages/EditProfilePage.qml"
        pushPageWithVm(path, vm)
    }

    function restart() {
        console.log("PAM")
        start(true)
    }
}
