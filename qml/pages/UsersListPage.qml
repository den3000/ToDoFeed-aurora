import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property UsersListVM viewModel
    onViewModelChanged: {
        viewModel.parent = this
        viewModel.start()
    }

    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Users List Page")
        }
        delegate: ListItem {
            Label {
                id: label
                text: qsTr("User %1").arg(model.index + 1)
                anchors.verticalCenter: parent.verticalCenter
                x: Theme.horizontalPageMargin
                color: Theme.primaryColor
            }
            onClicked: {
                viewModel.viewUserDetails(qsTr("userId_%1").arg(model.index + 1))
            }
        }
        model: 17
        VerticalScrollDecorator { }
    }
}
