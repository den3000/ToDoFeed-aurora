import QtQuick 2.0
import Sailfish.Silica 1.0

QmlCoordinator {
    signal unauthorized

    signal finishedToDoEditing

    function start(isRestart) {
        var vm = diProvider.toDoListVmInstance()
        vm.showToDo.connect(showToDo)
        vm.addToDo.connect(addToDo)
        vm.showUsersList.connect(showUsersList)
        vm.showSettings.connect(this.showSettings)
        finishedToDoEditing.connect(vm.reloadRequired)

        if (isRestart) {
            replaceAllPagesWithPageAndVm(toDoListPage, vm)
        } else {
            pushPageWithVm(toDoListPage, vm)
        }
    }

    function showToDo(toDoId) {
        var vm = diProvider.toDoDetailsVmInstance(toDoId)
        vm.editToDo.connect(editToDo)
        finishedToDoEditing.connect(vm.reloadRequired)
        pushPageWithVm(toDoDetailsPage, vm)
    }

    function addToDo() { editToDo("") }

    function editToDo(toDoId) {
        var vm = diProvider.editToDoVmInstance(toDoId)
        vm.finishedEditing.connect(handleToDoEditingFinished)
        pushPageWithVm(editToDoPage, vm)
    }

    function showUsersList() {
        var vm = diProvider.usersListVmInstance()
        vm.viewUserDetails.connect(showUserDetails)
        pushPageWithVm(usersListPage, vm)
    }

    function showUserDetails(userId) {
        var vm = diProvider.usersDetailsVmInstance(userId)
        vm.showToDo.connect(showToDo)
        pushPageWithVm(userDetailsPage, vm)
    }

    function showSettings() {
        var vm = diProvider.editProfileVmInstance()
        vm.unauthorized.connect(unauthorized)
        pushPageWithVm(editProfilePage, vm)
    }

    function handleToDoEditingFinished(toDoId) {
        console.log("editToDo " + toDoId)
        finishedToDoEditing()
        pageStack.pop()
    }
    function restart() {
        start(true)
    }
}
