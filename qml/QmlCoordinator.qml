import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property PageStack pageStack

    function pushPageWithVm(path, vm) {
        return pageStack.push(instantiatePage(path), {"viewModel": vm})
    }

    function replaceAllPagesWithPageAndVm(path, vm) {
        return pageStack.replaceAbove(null, instantiatePage(path), {"viewModel": vm})
    }

    function instantiatePage(path) {
        return Qt.createComponent(Qt.resolvedUrl(path))
    }
}
