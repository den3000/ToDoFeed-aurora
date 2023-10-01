import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property EditProfileVM viewModel
    onViewModelChanged: viewModel.parent = this
    allowedOrientations: Orientation.All

    Connections {
        target: viewModel
        onProfileLoaded: {
            pageHeader.title = isEdit ? qsTr("Edit Profile Page") : qsTr("Sign Up Page")
            btConfirm.text = isEdit ? qsTr("Update") : qsTr("Sign Up")
            btLogout.visible = isEdit
            btEraseAll.visible = isAdmin
            tfPassword.visible = !isEdit
            tfFirstName.text = firstName
            tfLastName.text = lastName
            tfAbout.text = about
        }
    }

    PageHeader {
        id: pageHeader
        objectName: "pageHeader"
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
            id: btConfirm
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
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
            id: btLogout
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: qsTr("Log Out")
            onClicked: { viewModel.onLogOut() }
        }

        Button {
            id: btEraseAll
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: qsTr("Erase All")
            onClicked: { viewModel.onEraseAll() }
        }
    }


    onStatusChanged: {
        switch (status) {
        case PageStatus.Inactive:
            return console.log("Inactive");
        case PageStatus.Activating:
            viewModel.start()
            return console.log("Activating");
        case PageStatus.Active:
            return console.log("Active");
        case PageStatus.Deactivating:
            return console.log("Deactivating");
        }
    }
}
