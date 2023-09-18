#ifndef PAGEDESTROYEDLISTENER_H
#define PAGEDESTROYEDLISTENER_H

#include <QObject>
#include <QDebug>

class PageDestroyedListener: public QObject
{
    Q_OBJECT
signals:
    void pageDestroyed();

public:
    PageDestroyedListener(QObject *parent = nullptr): QObject(parent) { qDebug(); }
    ~PageDestroyedListener() { qDebug(); }
};

/*
on caller page
    PageDestroyedListener {
        id: listener
    }

    Connections {
        target: listener
        onPageDestroyed: {
            console.log("next page destroyed")
        }
    }

    ...

    pageStack.push(Qt.resolvedUrl("NextPage.qml"), {
                       "pageDestroyedListener" : listener
                   })
*/

class PageDestroyedEmitter: public QObject
{
    Q_OBJECT

    // !!! IMPORTANT !!!
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)
    // !!! IMPORTANT !!!
    Q_PROPERTY(PageDestroyedListener * listener READ listener WRITE setListener)

    PageDestroyedListener * m_listener = nullptr;

public:
    PageDestroyedEmitter(QObject *parent = nullptr): QObject(parent) { qDebug(); }
    ~PageDestroyedEmitter() { emit m_listener->pageDestroyed(); qDebug(); }

    PageDestroyedListener * listener() { return m_listener; }
    void setListener(PageDestroyedListener * listener) { m_listener = listener; }
};

/*
on callee page

    PageDestroyedEmitter {
        id: emitter
    }

    property PageDestroyedListener pageDestroyedListener
    onPageDestroyedListenerChanged: {
        emitter.listener = pageDestroyedListener
    }

*/
#endif // PAGEDESTROYEDLISTENER_H
