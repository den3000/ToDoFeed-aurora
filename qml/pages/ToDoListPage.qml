import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0
import "../items"

Page {
    property bool isOwn: true
    property ToDoListVM viewModel
    onViewModelChanged: {
        viewModel.parent = this
        viewModel.start()
    }
    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("ToDoList Page")
            extraContent.children: [
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: isOwn ? qsTr("My") : qsTr("All")
                }
            ]
        }
        delegate:
        ToDoItem {
            toDoTitle: qsTr("ToDo %1").arg(model.index + 1)
            toDoStatus: "In Progress"
            onClicked: { viewModel.showToDo(qsTr("toDoId_%1").arg(model.index + 1)) }
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
                text: isOwn ? qsTr("Show All") : qsTr("Show My")
                onClicked: isOwn = !isOwn
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
