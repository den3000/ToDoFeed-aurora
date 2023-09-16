import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {
    property string toDoTitle
    property string toDoStatus

    Label {
        id: lblTitle
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: lblStatus.left
        leftPadding: Theme.horizontalPageMargin
        text: toDoTitle
        color: Theme.primaryColor
    }

    Label {
        id: lblStatus
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        rightPadding: Theme.horizontalPageMargin
        text: toDoStatus
        x: Theme.horizontalPageMargin
        color: Theme.primaryColor
    }
}
