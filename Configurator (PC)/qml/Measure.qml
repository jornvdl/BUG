/***************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.11
import QtQuick.Controls 2.4
GamePage {
    id: measurePage

    errorMessage: deviceHandler.error
    infoMessage: deviceHandler.info

    property real __timeCounter: 0
    property real __maxTimeCount: 60

    property real __rawbatt: 100
    property real __rawtimer: 300
    property real __newkeybind: 216

    property string __sleeptimer: qsTr("%1s").arg(__rawtimer)
    property real minHR: 0
    property string __modeview: qsTr("↑←↓→␣")
    property string __batteryperc: qsTr("N/A")

    function close() {
        //deviceHandler.stopMeasurement();
        deviceHandler.disconnectService();
        app.prevPage();
    }


    function updateLayout() {
        deviceHandler.sendLayout();
    }

    function layout0() {
        deviceHandler.updateLayout(0)
    }

    function layout1() {
        deviceHandler.updateLayout(1)
    }

    function layout2() {
        deviceHandler.updateLayout(2)
    }

    function layout3() {
        deviceHandler.updateLayout(3)
    }


    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -parent.height*0.4
        spacing: GameSettings.fieldHeight * 0.2

        Rectangle {
            id: infobox
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(measurePage.width, measurePage.height-GameSettings.fieldHeight*4) - 2*GameSettings.fieldMargin
            height: width*0.5
            radius: width*0.05
            color: GameSettings.viewColor

            Text {
                id: conftext
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: -parent.width*0.20
                horizontalAlignment: Text.AlignHLeft
                verticalAlignment: Text.AlignTop
                width: parent.width * 0.55
                text: "\nCurrent BUG configuration\n Key bind:   \t"+deviceHandler.keybind.toUpperCase()+"\n Sleeptimer:\t"+deviceHandler.timeout+"s\n Mode:         \t"+deviceHandler.mode+"\n Battery:     \t"+__batteryperc
                color: GameSettings.textColor
                fontSizeMode: Text.Fit
                minimumPixelSize: 10
                font.pixelSize: GameSettings.mediumFontSize
            }

            Image {
                id: bugfront
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: parent.width*0.28
                height: parent.height * 0.9
                width: height / 1.143
                source: "images/frontview.png"
                smooth: true
                antialiasing: true

                }
        }

        Text {
            id: keybindinfotext
            anchors.left: infobox.left
            anchors.leftMargin: GameSettings.fieldMargin * 0.4
            anchors.top: infobox.bottom
            anchors.topMargin: GameSettings.fieldMargin * 0.25
            height: GameSettings.fieldHeight * 0.75
            text: qsTr("Set key bind:")
            horizontalAlignment: Text.AlignLeft
            color: GameSettings.textColor
            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: GameSettings.mediumFontSize
        }

        Text {
            id: colourinfotext
            anchors.left: keybindinfotext.left
            anchors.top: keybindinfotext.bottom
            anchors.topMargin: GameSettings.fieldMargin * 0.05
            height: GameSettings.fieldHeight * 0.75
            text: qsTr("Set colour:")
            horizontalAlignment: Text.AlignLeft
            color: GameSettings.textColor
            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: GameSettings.mediumFontSize
        }

        Text {
            id: layoutinfotext
            anchors.left: keybindinfotext.left
            anchors.top: colourinfotext.bottom
            anchors.topMargin: GameSettings.fieldMargin * 0.05
            height: GameSettings.fieldHeight * 0.75
            text: qsTr("Set layout:")
            horizontalAlignment: Text.AlignLeft
            color: GameSettings.textColor
            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: GameSettings.mediumFontSize
        }

        Text {
            id: sleeptimerinfotext
            anchors.left: keybindinfotext.left
            anchors.top: layoutinfotext.bottom
            anchors.topMargin: GameSettings.fieldMargin * 0.05
            height: GameSettings.fieldHeight * 0.75
            text: qsTr("Set sleeptimer:")
            horizontalAlignment: Text.AlignLeft
            color: GameSettings.textColor
            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: GameSettings.mediumFontSize
        }

        Text {
            id: modeinfotext
            anchors.left: keybindinfotext.left
            anchors.top: sleeptimerinfotext.bottom
            anchors.topMargin: GameSettings.fieldMargin * 0.05
            height: GameSettings.fieldHeight * 0.75
            text: qsTr("Set use mode:")
            horizontalAlignment: Text.AlignLeft
            color: GameSettings.textColor
            fontSizeMode: Text.Fit
            minimumPixelSize: 10
            font.pixelSize: GameSettings.mediumFontSize
        }

        Rectangle {
            id: keybindbtn
            width: 0.3 * infobox.width
            height: GameSettings.fieldHeight * 0.6
            radius: GameSettings.buttonRadius
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 0.25*infobox.width
            anchors.verticalCenter: keybindinfotext.verticalCenter
            anchors.verticalCenterOffset: -0.2 * height
            color: modeselect.currentIndex === 5 ? GameSettings.buttonColor : GameSettings.disabledButtonColor
        }

        TextInput {
            id: keybindbtntxt
            width: keybindbtn.width
            height: keybindbtn.height
            //radius: GameSettings.buttonRadius
            anchors.horizontalCenter: keybindbtn.horizontalCenter
            anchors.verticalCenter: keybindbtn.verticalCenter
            color: modeselect.currentIndex === 5 ? GameSettings.textColor : GameSettings.disabledTextColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: height / 2
            text: deviceHandler.keybind

            activeFocusOnPress: modeselect.currentIndex === 5 ? true : false

            onFocusChanged:
                if (keybindbtntxt.focus) keybindbtntxt.text = "";
            onTextChanged: {
                if (text != "") {
                    console.log("Escaped keybind by key", keybindbtntxt.text);
                    keybindbtntxt.focus = false;
                    if (keybindbtntxt.text.length === 1) keybindbtntxt.text = keybindbtntxt.text.toUpperCase();
                    if (keybindbtntxt.text === " ") keybindbtntxt.text = "Space";
                    deviceHandler.sendKeybind(keybindbtntxt.text);
                }
            }

            }

        Rectangle {
            id: colourbtn
            width: 0.3 * infobox.width
            height: GameSettings.fieldHeight * 0.6
            radius: GameSettings.buttonRadius
            anchors.horizontalCenter: keybindbtn.horizontalCenter
            anchors.verticalCenter: colourinfotext.verticalCenter
            anchors.verticalCenterOffset: -0.2 * height
            color: Qt.rgba((deviceHandler.colour >> 16 & 0xFF) / 255,
                           (deviceHandler.colour >> 8  & 0xFF) / 255,
                           (deviceHandler.colour       & 0xFF) / 255);
        }

        TextInput {
            id: colourbtntxt
            width: keybindbtn.width
            height: keybindbtn.height
            //radius: GameSettings.buttonRadius
            anchors.horizontalCenter: colourbtn.horizontalCenter
            anchors.verticalCenter: colourbtn.verticalCenter
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: height / 2
            text: deviceHandler.colour.toString(16)


            validator: RegExpValidator { regExp: /[0-9A-Fa-f]+/ }

            onFocusChanged:
                if (colourbtntxt.focus) colourbtntxt.text = "";
            onTextChanged: {
                if (text != "") {
                    if (text.length === 6) {
                        colourbtntxt.focus = false;
                        // TOFIX: Convert to int first
                        console.log("Color set to","#"+text);
                        colourbtn.color = "#"+text;
                        console.log("Lightness:");
                        deviceHandler.updateColour(text);
                    }
                }

            }

            }

        Layout0Button {
            id: layoutbtn1
            width: 0.04 * infobox.width
            height: width
            radius: GameSettings.buttonRadius * 0.2
            anchors.horizontalCenter: colourbtn.horizontalCenter
            anchors.verticalCenter: layoutbtn2.verticalCenter
            anchors.verticalCenterOffset: -1.55 * height

            onClicked: layout0()


        }

        Layout1Button {
            id: layoutbtn2
            width: 0.04 * infobox.width
            height: width
            radius: GameSettings.buttonRadius * 0.2
            anchors.right: layoutbtn1.left
            anchors.rightMargin: 0.55*width
            anchors.verticalCenter: layoutinfotext.verticalCenter
            anchors.verticalCenterOffset: 0.25 * height

            onClicked: layout1()
        }

        Layout2Button {
            id: layoutbtn3
            width: 0.04 * infobox.width
            height: width
            radius: GameSettings.buttonRadius * 0.2
            anchors.verticalCenter: layoutbtn2.verticalCenter
            anchors.left: layoutbtn2.right
            anchors.leftMargin: 0.55*width

            onClicked: layout2()
        }

        Layout3Button {
            id: layoutbtn4
            width: 0.04 * infobox.width
            height: width
            radius: GameSettings.buttonRadius * 0.2
            anchors.verticalCenter: layoutbtn2.verticalCenter
            anchors.left: layoutbtn3.right
            anchors.leftMargin: 0.55*width

            onClicked: layout3()
        }

        Rectangle {
            width: 0.3 * infobox.width
            height: GameSettings.fieldHeight * 0.6
            radius: GameSettings.buttonRadius
            anchors.horizontalCenter: keybindbtn.horizontalCenter
            anchors.verticalCenter: sleeptimerinfotext.verticalCenter
            anchors.verticalCenterOffset: -0.2 * height
            color: GameSettings.buttonColor
        }

        TextInput {
            id: timerbtn
            width: 0.3 * infobox.width
            height: GameSettings.fieldHeight * 0.6
            //radius: GameSettings.buttonRadius
            anchors.horizontalCenter: keybindbtn.horizontalCenter
            anchors.verticalCenter: sleeptimerinfotext.verticalCenter
            anchors.verticalCenterOffset: -0.2 * height
            color: GameSettings.textColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            validator: IntValidator { bottom: 0; top: 65535 }
            font.pixelSize: height / 2
            text: deviceHandler.timeout
        }

        ComboBox {
            id: modeselect
            width: keybindbtn.width
            height: GameSettings.fieldHeight * 0.6
            anchors.horizontalCenter: keybindbtn.horizontalCenter
            anchors.verticalCenter: modeinfotext.verticalCenter
            anchors.verticalCenterOffset: -0.2 * height

            model: ListModel {
                id: modeItems
                ListElement { text: "Arrows"}
                ListElement { text: "Arrows + space"}
                ListElement { text: "WASD"}
                ListElement { text: "WASD + space"}
                ListElement { text: "Presenter mode"}
                ListElement { text: "Custom key"}
            }
            onCurrentIndexChanged: {
                deviceHandler.updateMode(currentIndex);
                console.log("Current index: ",currentIndex);
            }
        }

        Keys.onPressed: {
            if ((event.key === 16777221 | event.key === 16777220) & timerbtn.activeFocus === true) {
                timerbtn.focus = false;
                console.log("Escaped timer. Timer = ", timerbtn.text);
                onClicked: deviceHandler.sendTimeout(timerbtn.text);
            }
            if ((event.key === 16777216) & timerbtn.activeFocus === true) {
                timerbtn.focus = false;
                timerbtn.text = deviceHandler.timeout;
                console.log("Escaped timer. Timer = ", timerbtn.text);
            }
            if (keybindbtntxt.activeFocus) {
                switch (event.key) {
                case 16777220:
                    console.log("Escaped keybind by enter");
                    keybindbtntxt.text = "Enter";
                    keybindbtntxt.focus = false;
                    break;
                case 16777221:
                    console.log("Escaped keybind by enter");
                    keybindbtntxt.text = "Enter";
                    keybindbtntxt.focus = false;
                    break;
                case 16777234:
                    console.log("Escaped keybind by arrow left");
                    keybindbtntxt.text = "←";
                    keybindbtntxt.focus = false;
                    break;
                case 16777235:
                    console.log("Escaped keybind by arrow up");
                    keybindbtntxt.text = "↑";
                    keybindbtntxt.focus = false;
                    break;
                case 16777236:
                    console.log("Escaped keybind by arrow right");
                    keybindbtntxt.text = "→";
                    keybindbtntxt.focus = false;
                    break;
                case 16777237:
                    console.log("Escaped keybind by arrow down");
                    keybindbtntxt.text = "↓";
                    keybindbtntxt.focus = false;
                    break;
                case 16777249:
                    console.log("Escaped keybind by ctrl");
                    keybindbtntxt.text = "Ctrl";
                    keybindbtntxt.focus = false;
                    break;
                case 16777251:
                    console.log("Escaped keybind by alt");
                    keybindbtntxt.text = "Alt";
                    keybindbtntxt.focus = false;
                    break;
                case 16777248:
                    console.log("Escaped keybind by shift");
                    keybindbtntxt.text = "Shift";
                    keybindbtntxt.focus = false;
                    break;
                case 16777216:
                    console.log("Escaped keybind by escape");
                    keybindbtntxt.text = "Escape";
                    keybindbtntxt.focus = false;
                    break;
                }
            }
        }
    }

    GameButton {
        id: rstButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: GameSettings.fieldMargin
        width: parent.width*0.5 - 1.5 * GameSettings.fieldMargin
        anchors.horizontalCenterOffset: -0.5*GameSettings.fieldMargin - 0.5*width
        height: GameSettings.fieldHeight
        enabled: true
        radius: GameSettings.buttonRadius

        onClicked: {
            deviceHandler.updateMode(6);
        }

        Text {
            anchors.centerIn: parent
            font.pixelSize: GameSettings.tinyFontSize
            text: qsTr("Set to Factory Settings")
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            color: rstButton.enabled ? GameSettings.textColor : GameSettings.disabledTextColor
        }
    }

    GameButton {
        id: idButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: GameSettings.fieldMargin
        width: parent.width*0.5 - 1.5 * GameSettings.fieldMargin
        anchors.horizontalCenterOffset: 0.5*GameSettings.fieldMargin + 0.5*width
        height: GameSettings.fieldHeight
        radius: GameSettings.buttonRadius

        onClicked: deviceHandler.updateMode(7);

        Text {
            anchors.centerIn: parent
            font.pixelSize: GameSettings.tinyFontSize
            text: qsTr("Identify")
            wrapMode: Text.WordWrap
            color: deviceHandler.getIDflg ? GameSettings.buttonPressedColor : GameSettings.textColor
        }


    }
}
