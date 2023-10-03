import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {
    property string toDoTitle
    property string toDoStatus
    property string visibility
    property string userId

    Label {
        id: lblTitle
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: lblStatus.left
        leftPadding: Theme.horizontalPageMargin
        text: toDoTitle
        color: Theme.primaryColor
        wrapMode: Text.Wrap
    }

    Label {
        id: lblStatus
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        rightPadding: Theme.horizontalPageMargin
        text: toDoStatus
        color: Theme.primaryColor
    }

    Label {
        id: lblVisibility
        anchors.top: lblTitle.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: lblUserId.left
        leftPadding: Theme.horizontalPageMargin
        horizontalAlignment: Text.AlignLeft
        text: visibility
        color: Theme.primaryColor
        fontSizeMode: "Fit"
    }

    Label {
        id: lblUserId
        anchors.top: lblStatus.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        rightPadding: Theme.horizontalPageMargin
        horizontalAlignment: Text.AlignRight
//        text: userId // uncomment this when needed
        color: Theme.primaryColor
        fontSizeMode: "Fit"
    }
}
