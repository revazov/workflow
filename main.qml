import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: 0

        Page {
            ListView{
                id: missionView
                anchors.fill: parent
                anchors.margins: 5
                snapMode: ListView.SnapOneItem
                boundsBehavior: Flickable.StopAtBounds

                model: missionModel
                currentIndex: 0

                highlightFollowsCurrentItem: true
                header: Rectangle{
                    color: "cadetBlue"
                    width: parent.width
                    height: 100
                }

                delegate: MissionDelegate{
                    property variant itemData: model
                    onWrapperClicked: {
                        console.log(index)
                        missionView.currentIndex = index
                        swipeView.currentIndex = 1;
                    }
                }
                highlight: Rectangle {
                    width: 180
                    height: 40
                    color: "white"
                    radius: 5
                    border.width: 3
                    border.color: "mediumturquoise"
                    y: missionView.currentItem.y
                    x: missionView.currentItem.x
                    z: 2
                    opacity: 0.3
                    Behavior on y {
                        SpringAnimation {
                            spring: 3
                            damping: 0.2
                        }
                    }
                }
                onCurrentItemChanged: {
                    console.log("current items index " + currentItem.itemData.name)
                }
            }
        }

        Page {
            Flickable{
                id: dashboard
                anchors.fill: parent
                flickableDirection: Flickable.VerticalFlick
                contentWidth: contentItem.childrenRect.width; contentHeight: contentItem.childrenRect.height
                Column{
                    Repeater{
                        model: 10
                        Column{
                            Rectangle{
                                width: 30
                                height: 300
                                color: "black"
                            }
                            Rectangle{
                                width: 30
                                height: 30
                                color: "blue"
                            }
                        }
                    }
                }
            }
        }
    }
}
