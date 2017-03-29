import QtQuick 2.7
import QtQuick.Controls 2.0

import com.vision.quick 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Column{
        spacing: 20
        anchors.fill: parent
        Svg{
            height: 50
            source:"qrc:/resources/android-more-horizontal.svg"
            color : "#ffff00"
            id : svg

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true

                onEntered: {
                    svg.color = "#ff0000"
                }

                onExited: {
                    svg.color = "#ffff00"
                }
            }
        }

        Svg{
            height: 50
            source:"qrc:/resources/android-more-vertical.svg"
            color : "#00ffff"

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true

                onEntered: {
                    parent.color = "#ff0000"
                }

                onExited: {
                    parent.color = "#00ffff"
                }
            }
        }

        Svg{
            height: 50
            source:"qrc:/resources/android-navigate.svg"
            color : "blue"

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true

                onEntered: {
                    parent.color = "black"
                }

                onExited: {
                    parent.color = "blue"
                }
            }
        }

        Svg{
            height: 150
            width : 80
            source:"qrc:/resources/android-notifications.svg"
            color : "#ffff00"

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true

                onEntered: {
                    parent.color = "#ff0000"
                }

                onExited: {
                    parent.color = "#ffff00"
                }
            }
        }
    }


}
