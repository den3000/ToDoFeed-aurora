import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property RestApiTestVM viewModel
    onViewModelChanged: viewModel.parent = this

    objectName: "restApiTestPage"
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("RestApiTest")
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Registration"
            onClicked: { viewModel.executeRegister() }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Get All Users"
            onClicked: { viewModel.executeGetAllUsers() }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Edit Profile"
            onClicked: { viewModel.executeEditProfile() }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Add ToDos"
            onClicked: { viewModel.executeAddToDo() }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Get All ToDos"
            onClicked: { viewModel.executeGetAllToDos() }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Get My ToDos"
            onClicked: { viewModel.executeGetMyToDos() }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Edit ToDo"
            onClicked: { viewModel.executeEditToDo() }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Erase All"
            onClicked: { viewModel.executeEraseAll() }
        }

    }


}

