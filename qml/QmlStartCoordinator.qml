import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

QmlCoordinator {
    signal authorized

    function start(isRestart) {
        var vm = diConsumer.startVmInstance()
        vm.login.connect(login)
        vm.signup.connect(signup)

        if (isRestart) {
            replaceAllPagesWithPageAndVm(startPage, vm)
        } else {
            pushPageWithVm(startPage, vm)
        }
    }

    function login() {
        var vm = diConsumer.loginVmInstance()
        vm.authorized.connect(authorized)
        pushPageWithVm(loginPage, vm)
    }

    function signup() {
        var vm = diConsumer.signupVmInstance()
        vm.authorized.connect(authorized)
        pushPageWithVm(editProfilePage, vm)
    }

    function restart() {
        start(true)
    }
}
