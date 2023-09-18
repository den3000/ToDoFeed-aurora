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
            toDoTitle: model.title
            toDoStatus: model.status
            userId: model.userId
            visibility: model.visibility
            onClicked: { viewModel.showToDo(model.toDoId) }
        }
        model: viewModel
        VerticalScrollDecorator { }
    }
}
