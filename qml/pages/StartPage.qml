import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property StartVM viewModel                  // !!! IMPORTANT !!!
    onViewModelChanged: viewModel.parent = this // !!! IMPORTANT !!!
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("Start Page")
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "LogIn"
            onClicked: login()
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Signup"
            onClicked: signup()
        }
    }

}
