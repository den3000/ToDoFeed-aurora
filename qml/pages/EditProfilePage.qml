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
            if (viewModel.signup()) {
                return qsTr("Sign Up Page")
            } else {
                return qsTr("Edit Profile Page")
            }
        }
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: {
                if (viewModel.signup()) {
                    return qsTr("Sign Up")
                } else {
                    return qsTr("Log Out")
                }
            }
            onClicked: { viewModel.confirmPressed() }
        }
    }
}
