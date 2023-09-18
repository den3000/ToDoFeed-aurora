import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property EditToDoVM viewModel
    onViewModelChanged: {
        viewModel.parent = this
        viewModel.start()
    }

    Connections {
        target: viewModel
        onToDoDetailsLoaded: {
            tfTitle.text = title
            tfDesciption.text = description
            console.log(qsTr("s: %1 v: %2").arg(statusIdx).arg(visibilityIdx))
            cbStatus.currentIndex = statusIdx
            cbVisibility.currentIndex = visibilityIdx
        }
    }

    allowedOrientations: Orientation.All

    PageHeader {
        title: {
            if (viewModel.isEdit()) {
                return qsTr("Edit ToDo Page")
            } else {
                return qsTr("Add ToDo Page")
            }
        }
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent

        TextField {
            id: tfTitle
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
        }

        TextEdit {
            id: tfDesciption
            anchors { left: parent.left; right: parent.right; margins: 2 * Theme.horizontalPageMargin }
        }

        ComboBox {
            id: cbStatus
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            menu: ContextMenu {
                anchors { left: parent.left; right: parent.right; margins: 0 }
                MenuItem { text: "ToDo" }
                MenuItem { text: "In Progress" }
                MenuItem { text: "Done" }
            }
            onCurrentIndexChanged: {
                console.log(qsTr("new status index: %1").arg(currentIndex))
            }
        }

        ComboBox {
            id: cbVisibility
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            menu: ContextMenu {
                anchors { left: parent.left; right: parent.right; margins: 0 }
                MenuItem { text: "Own" }
                MenuItem { text: "For All" }
            }
            onCurrentIndexChanged: {
                console.log(qsTr("new visibility index: %1").arg(currentIndex))
            }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Confirm"
            onClicked: { viewModel.confirm(
                tfTitle.text,
                tfDesciption.text,
                cbStatus.currentIndex,
                cbVisibility.currentIndex
            )}
        }
    }
}
