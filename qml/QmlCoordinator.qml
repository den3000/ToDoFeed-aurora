import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property PageStack pageStack

    function instantiatePage(path) {
        return Qt.createComponent(Qt.resolvedUrl(path)).createObject();
    }
}
