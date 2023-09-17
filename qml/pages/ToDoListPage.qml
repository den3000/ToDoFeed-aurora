import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0
import "../items"

Page {
    property ToDoListVM viewModel
    onViewModelChanged: {
        viewModel.parent = this
        viewModel.start()
    }

    property string headerText: qsTr("My")
    property string miChangeVisibility: qsTr("Show All")
    Connections {
        target: viewModel
        onVisibilityChanged: {
            headerText = isOwn ? qsTr("My") : qsTr("All")
            miChangeVisibility = isOwn ? qsTr("Show All") : qsTr("Show My")
        }
    }

    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("ToDoList Page")
            extraContent.children: [
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: headerText
                }
            ]
        }
        delegate:
        ToDoItem {
            toDoTitle: qsTr("ToDo %1").arg(model.index + 1)
            toDoStatus: "In Progress"
            onClicked: { viewModel.showToDo("2fec3dc0-a293-4dfe-99a4-f158cbb91fd2") }
        }
        model: 17
        VerticalScrollDecorator { }

        PullDownMenu {
            MenuItem {
                text: qsTr("Go to settings")
                onClicked: viewModel.showSettings()
            }
            MenuItem {
                text: qsTr("Go to users")
                onClicked: viewModel.showUsersList()
            }
            MenuItem {
                text: miChangeVisibility
                onClicked: viewModel.changeVisibility()
            }
            MenuItem {
                text: qsTr("Add Todo")
                onClicked: viewModel.callAddToDo()
            }
            MenuItem {
                text: qsTr("Reload")
                onClicked: viewModel.start()
            }
        }

    }
}
