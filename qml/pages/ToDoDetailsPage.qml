import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property ToDoDetailsVM viewModel
    onViewModelChanged: {
        viewModel.parent = this
        viewModel.start()
    }

    Connections {
        target: viewModel
        onToDoDetailsLoaded: {
            header.title = title
            tDescription.text = description
            tStatus.text = status
            tVisibility.text = visibility
            btEdit.visible = isEditable
        }
    }

    allowedOrientations: Orientation.All

    PageHeader {
        id: header
        objectName: "pageHeader"
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent

        Text {
            id: tDescription
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
        }

        Text {
            id: tStatus
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
        }

        Text {
            id: tVisibility
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
        }

        Button {
            id: btEdit
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Edit Todo"
            visible: false
            onClicked: { viewModel.onEditToDo() }
        }
    }
}
