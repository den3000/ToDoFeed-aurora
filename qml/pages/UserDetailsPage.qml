import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0
import "../items"

Page {
    property string headerTitle: ""
    property UserDetailsVM viewModel
    onViewModelChanged: {
        viewModel.parent = this
        viewModel.start()
    }

    Connections {
        target: viewModel
        onUserDetailsLoaded: {
            headerTitle = userName
        }
    }

    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: headerTitle
        }
        delegate: ToDoItem {
            toDoTitle: qsTr("ToDo %1").arg(model.index + 1)
            toDoStatus: "In Progress"
            onClicked: { viewModel.showToDo(qsTr("toDoId_%1").arg(model.index + 1)) }
        }
        model: 17
        VerticalScrollDecorator { }
    }
}
