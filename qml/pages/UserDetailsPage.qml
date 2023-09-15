import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property UserDetailsVM viewModel
    onViewModelChanged: viewModel.parent = this

    objectName: "signupPage"
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("User Details Page")
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "View Todo"
            onClicked: { viewModel.showToDo("some_id") }
        }
    }
}
