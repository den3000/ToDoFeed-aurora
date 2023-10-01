import QtQuick 2.0
import Sailfish.Silica 1.0

QmlCoordinator {
    signal unauthorized

    signal toDoEdited(string toDoId)

    function start(isRestart) {
        var vm = diConsumer.toDoListVmInstance()
        vm.showToDo.connect(showToDo)
        vm.addToDo.connect(addToDo)
        vm.showUsersList.connect(showUsersList)
        vm.showSettings.connect(this.showSettings)
        toDoEdited.connect(vm.reloadRequired)

        if (isRestart) {
            replaceAllPagesWithPageAndVm(toDoListPage, vm)
        } else {
            pushPageWithVm(toDoListPage, vm)
        }
    }

    function showToDo(toDoId) {
        var vm = diConsumer.toDoDetailsVmInstance(toDoId)
        vm.editToDo.connect(editToDo)
        toDoEdited.connect(vm.reloadRequired)
        pushPageWithVm(toDoDetailsPage, vm)
    }

    function addToDo() { editToDo("") }

    function editToDo(toDoId) {
        var vm = diConsumer.editToDoVmInstance(toDoId)
        vm.finishedEditing.connect(toDoEditingFinished)
        pushPageWithVm(editToDoPage, vm)
    }

    function showUsersList() {
        var vm = diConsumer.usersListVmInstance()
        vm.viewUserDetails.connect(showUserDetails)
        pushPageWithVm(usersListPage, vm)
    }

    function showUserDetails(userId) {
        var vm = diConsumer.usersDetailsVmInstance(userId)
        vm.showToDo.connect(showToDo)
        pushPageWithVm(userDetailsPage, vm)
    }

    function showSettings() {
        var vm = diConsumer.editProfileVmInstance()
        vm.unauthorized.connect(unauthorized)
        pushPageWithVm(editProfilePage, vm)
    }

    function toDoEditingFinished(toDoId) {
        toDoEdited(toDoId)
        popCurrentPage()
    }

    function restart() {
        start(true)
    }
}