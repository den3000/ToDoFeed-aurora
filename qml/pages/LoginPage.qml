import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property LoginVM viewModel
    onViewModelChanged: viewModel.parent = this
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("LoginPage")
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

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "LogIn"
            onClicked: { viewModel.loginPressed(tfPassword.text) }
        }
    }
}
