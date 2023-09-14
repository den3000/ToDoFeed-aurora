import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property PageStack pageStack

    objectName: "pageStackCppWrapper"

    /*
        pageStack.push is a variadic function
        https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/arguments

        Probably it is a decision made by Aurora devs to implement one function in this
        way instead of implementing somthing like 5-6 functions, since you can push page
        by string (url), Item, Component, with or without properties, or even push array
        of pages (as string, Item or Component) and with or without custom properties.

        Qt does not support calls to variadic function from C++ so we need to have some
        non variadic functions in Qml to call from C++ which will trigger variadic function
        version.

        Possible alternatives
        1. In Qml you can call your Cpp class in something like the following:

            function foo() {
                someCppClassName.bar(pageStack.push)
            }
        and in cpp something like

        SomeCppClassName {
            ...
            Q_INVOKABLE bar(JSValue callback);
            ...
        }
        this in the end might give us a reference to jsCallback on c++ side
        that we can try to execute with `.call()`

        2. On cpp side try to find pageStack object, then find it `push` property
        and cast it to jsvalue.

    */
    function push(page, properties) {
        pageStack.push(page, properties)
    }

    function replaceAll(page, properties) {
        pageStack.clear()
        pageStack.push(page, properties)
    }
}
