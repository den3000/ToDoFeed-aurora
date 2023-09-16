import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0
import "../items"

Page {
    property UserDetailsVM viewModel
    onViewModelChanged: viewModel.parent = this

    objectName: "signupPage"
    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("User Details %1 Page").arg(viewModel.userName())
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
