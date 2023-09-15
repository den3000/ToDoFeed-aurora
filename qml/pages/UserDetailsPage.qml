import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

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
        delegate: ListItem {
            Label {
                id: label
                text: qsTr("ToDo %1").arg(model.index + 1)
                anchors.verticalCenter: parent.verticalCenter
                x: Theme.horizontalPageMargin
                color: Theme.primaryColor
            }
            onClicked: { viewModel.showToDo(qsTr("toDoId_%1").arg(model.index + 1)) }
        }
        model: 17
        VerticalScrollDecorator { }
    }
}
