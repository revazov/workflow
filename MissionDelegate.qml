import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle{
    id: wrapper
    property bool isActive: false
    property bool isEditable: false
    signal wrapperClicked
    width: 300
    height: 100
    color: "white"
    border.width: 1
    border.color: isActive? "black" : "grey"
    radius: 5
    z: 1

    Rectangle{
        id: nameWrapper
        width: wrapper.width - 10
        height: nameText.height + 10
        anchors.top: wrapper.top
        anchors.topMargin: 5
        anchors.horizontalCenter: wrapper.horizontalCenter
        radius: 5
        color: Qt.formatDateTime(new Date(), "yyyy-MM-dd | HH-mm") > end_date? "firebrick" : "SteelBlue"
        opacity: wrapper.isActive? 1 : 0.5
        z: 2
    }

    TextArea {
        id: nameText
        width: nameWrapper.width
        anchors.centerIn: nameWrapper
        text: name
        readOnly: !isEditable
        font.family: "Mongolian Baity"
        color: wrapper.isActive? "white" : "black"
        wrapMode: TextEdit.Wrap
        z: 3
    }
    Rectangle{
        id: infoWrapper
        width: wrapper.width - 10
        anchors.top: nameWrapper.bottom
        anchors.bottom: wrapper.bottom
        anchors.margins: 5
        anchors.horizontalCenter: wrapper.horizontalCenter
        color: wrapper.isActive? "grey" : "white"
        Column{
            spacing: 2
            anchors.horizontalCenter: infoWrapper.horizontalCenter
            Text{text: qsTr("Started: ") + start_date; color: wrapper.isActive? "white" : "black"}
            Text{text: qsTr("Deadline: ") + end_date; color: wrapper.isActive? "white" : "black"}
            Text{}
        }
    }

    MouseArea{
        anchors.fill: parent
        propagateComposedEvents: true
        hoverEnabled: true
        acceptedButtons: Qt.AllButtons
        onEntered: {
            isActive = true;
        }
        onExited: {isActive = false}
        onClicked: {
            wrapperClicked()
            mouse.accepted = true
        }
//        onPressed: mouse.accepted = false;
//        onReleased: mouse.accepted = false;
//        onDoubleClicked: mouse.accepted = false;
//        onPositionChanged: mouse.accepted = false;
//        onPressAndHold: mouse.accepted = false;
        z: 4

    }


}
