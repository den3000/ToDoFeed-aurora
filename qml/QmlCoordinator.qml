import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property PageStack pageStack

    property string startPage:  "pages/StartPage.qml"
    property string loginPage: "pages/LoginPage.qml"
    property string editProfilePage: "pages/EditProfilePage.qml"
    property string toDoListPage: "pages/ToDoListPage.qml"
    property string toDoDetailsPage: "pages/ToDoDetailsPage.qml"
    property string editToDoPage: "pages/EditToDoPage.qml"
    property string usersListPage: "pages/UsersListPage.qml"
    property string userDetailsPage: "pages/UserDetailsPage.qml"

    function pushPageWithVm(path, vm) {
        return pageStack.push(instantiatePage(path), {"viewModel": vm})
    }

    function replaceAllPagesWithPageAndVm(path, vm) {
        return pageStack.replaceAbove(null, instantiatePage(path), {"viewModel": vm})
    }

    function popCurrentPage() {
        pageStack.pop()
    }

    function instantiatePage(path) {
        return Qt.createComponent(Qt.resolvedUrl(path))
    }
}
