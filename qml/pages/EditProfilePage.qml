import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property EditProfileVM viewModel
    onViewModelChanged: viewModel.parent = this

    objectName: "signupPage"
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: {
            if (viewModel.edit()) {
                return qsTr("Edit Profile Page")
            } else {
                return qsTr("Sign Up Page")
            }
        }
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent


        TextField {
            id: tfPassword
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            placeholderText: "Password"
            visible: !viewModel.edit()
        }

        TextField {
            id: tfFirstName
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            placeholderText: "First Name"
        }

        TextField {
            id: tfLastName
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            placeholderText: "Last Name"
        }

        TextField {
            id: tfAbout
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            placeholderText: "About"
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: {
                if (viewModel.edit()) {
                    return qsTr("Update")
                } else {
                    return qsTr("Sign Up")
                }
            }
            onClicked: {
                viewModel.onConfirm(
                    tfPassword.text,
                    tfFirstName.text,
                    tfLastName.text,
                    tfAbout.text
                )
            }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: qsTr("Log Out")
            onClicked: { viewModel.onLogOut() }
            visible: viewModel.edit()
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: qsTr("Erase All")
            onClicked: { viewModel.onEraseAll() }
            visible: viewModel.admin()
        }
    }
}
