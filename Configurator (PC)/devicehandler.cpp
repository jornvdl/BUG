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

#include "devicehandler.h"
#include "deviceinfo.h"
#include <QtEndian>
#include <QRandomGenerator>
#include <QTextStream>
#include <QKeyEvent>
#include <QList>


QString gattUUID = "0ba682ae-4f1f-4e9b-be2a-809c224540fd";
QString bindUUID = "3e7f5770-d6b7-4709-9b4b-951c63f97aaa";
QString indcUUID = "6f1f3Ce2-cb88-4c5a-9ba1-6e19369b8bbb";
QString timeUUID = "6de0e9a1-7f07-4e64-81b0-a8ca334bcccc";
QString settUUID = "99503c7d-6924-413c-bb7d-db7e913fbddd";

QLowEnergyCharacteristic bindChar;
QLowEnergyCharacteristic layoutChar;
QLowEnergyCharacteristic timeoutChar;
QLowEnergyCharacteristic infoChar;

QTextStream out(stdout);

int __timeout;
bool __layout[4];
int __mode;
int __colour;

bool flgID;

bool BLEUpdated = true;

void DeviceHandler::fetchBLEData() const
{
    // layout
    QString tempresult;
    QByteArray a = layoutChar.value();
    int result;
    if (a.isEmpty()) {
        out << "None" << Qt::endl;
        __layout[0] = 0;
        __layout[1] = 0;
        __layout[2] = 0;
        __layout[3] = 0;
    }

    bool valid;
    QString templayout;
    tempresult += a.toHex();
    out << "Tempresult layout: " << tempresult << Qt::endl;
    templayout = tempresult.right(1);
    result = templayout.toInt(&valid,16);
    out << "            layout:" << result << Qt::endl;
    __layout[0] = (result & 0b0001) == 0b0001;
    __layout[1] = (result & 0b0010) == 0b0010;
    __layout[2] = (result & 0b0100) == 0b0100;
    __layout[3] = (result & 0b1000) == 0b1000;

    // colour
    QString tempcolour;
    tempcolour = tempresult.right(8);
    tempcolour = tempcolour.left(6);
    __colour = tempcolour.toInt(&valid, 16);

    a.clear();
    a += timeoutChar.value();
    if (a.isEmpty()) {
        out << "None" << Qt::endl;
        __timeout = 0 ;
    }

    tempresult.clear();
    tempresult += a.toHex();
    tempresult = tempresult.left(4);
    out << "Tempresult timeout: " << tempresult << Qt::endl;
    __timeout = tempresult.toInt(&valid,16);

    out << " timeout: " << __timeout << Qt::endl;

}

QString DeviceHandler::getKeybind() const
{
    QByteArray a = bindChar.value();
    int result;
    QString tempresult;
    if (a.isEmpty()) {
        out << "None" << Qt::endl;
        return "None";
    }

    tempresult = a;
    bool valid;
    tempresult += a.toHex();
    tempresult.remove(0,1);
    tempresult.remove(2,6);
    result = tempresult.toInt(&valid,16);

    // Lookup table to convert some values to icons (space, arrows, etc)
    QString strResult;
    switch (result) {
    case 32:
        strResult = "Space";
        break;
    case 80:
        strResult = "l Ctrl";
        break;
    case 81:
        strResult = "l Shift";
        break;
    case 82:
        strResult = "l Alt";
        break;
    case 84:
        strResult = "r Ctrl";
        break;
    case 85:
        strResult = "r Shift";
        break;
    case 86:
        strResult = "r Alt";
        break;
    case 215:
        strResult = "→";
        break;
    case 216:
        strResult = "←";
        break;
    case 217:
        strResult = "↓";
        break;
    case 218:
        strResult = "↑";
        break;
    case 177:
        strResult = "Escape";
        break;
    case 178:
        strResult = "Bckspc";
        break;
    case 0xB3:
        strResult = "Tab";
        break;
    case 0xD1:
        strResult = "Insert";
        break;
    case 0xD2:
        strResult = "Tab";
        break;
    case 0xD3:
        strResult = "PgUp";
        break;
    case 0xD4:
        strResult = "Delete";
        break;
    case 0xD5:
        strResult = "End";
        break;
    case 0xD6:
        strResult = "PgDown";
        break;
    default:
        char tmpchar = result;
        strResult = tmpchar;
        break;
    }

    out << "Keybind: int=" << result << " char=" << strResult << Qt::endl;

    return strResult;
}

int DeviceHandler::getColour() const
{
    // if value updated in BLE, fetch it.
    if (BLEUpdated) {
        fetchBLEData();
        BLEUpdated=false;
    }

    out << "Colour = " << __colour << Qt::endl;

    return __colour;
}

bool DeviceHandler::getLayout0() const
{
    // if value updated in BLE, fetch it.
    if (BLEUpdated) {
        fetchBLEData();
        BLEUpdated=false;
    }

    out << "Layout[0] = " << __layout[0] << Qt::endl;

    return __layout[0];
}

bool DeviceHandler::getLayout1() const
{
    // if value updated in BLE, fetch it.
    if (BLEUpdated) {
        fetchBLEData();
        BLEUpdated=false;
    }

    out << "Layout[1] = " << __layout[1] << Qt::endl;

    return __layout[1];
}

bool DeviceHandler::getLayout2() const
{
    // if value updated in BLE, fetch it.
    if (BLEUpdated) {
        fetchBLEData();
        BLEUpdated=false;
    }

    out << "Layout[2] = " << __layout[2] << Qt::endl;

    return __layout[2];
}

bool DeviceHandler::getLayout3() const
{
    // if value updated in BLE, fetch it.
    if (BLEUpdated) {
        fetchBLEData();
        BLEUpdated=false;
    }

    out << "Layout[3] = " << __layout[3] << Qt::endl;

    return __layout[3];
}

int DeviceHandler::getTimeout() const
{
    if (BLEUpdated) {
        fetchBLEData();
        BLEUpdated=false;
    }

    out << "Timeout = " << __timeout << Qt::endl;
    return __timeout;
}

int DeviceHandler::getMode() const
{
    if (BLEUpdated) {
        fetchBLEData();
        BLEUpdated=false;
    }

    out << "Mode = " << __mode << Qt::endl;
    return __mode;
}

bool DeviceHandler::getIDflg() const
{
    return flgID;
}

void DeviceHandler::updateLayout(int i)
{
    __layout[i] = !__layout[i];

    emit dataChanged();
    out << "layout" << i << " set to " << __layout[i] << Qt::endl;

    sendLayout();
}

void DeviceHandler::updateColour(QString from_gui)
{
    out << "from_gui: " << from_gui << Qt::endl;
    __colour = from_gui.toInt(NULL, 16);

    sendLayout();

    emit dataChanged();
}

void DeviceHandler::updateMode(int k)
{
    char mout[4];

    if (k < 6) __mode= k;


    switch (__mode) {
    case 0: // Arrows
       mout[1] = 0x00;
       mout[2] = 0x11;
       mout[3] = 0x11;
        break;
    case 1: // Arrows with space
       mout[1] = 0x01;
       mout[2] = 0x11;
       mout[3] = 0x11;
        break;
    case 2: // WASD
       mout[1] = 0x10;
       mout[2] = 0x11;
       mout[3] = 0x11;
        break;
    case 3: // WASD with space
       mout[1] = 0x11;
       mout[2] = 0x11;
       mout[3] = 0x11;
        break;
    case 4: // Arrow left and right (presenter)
       mout[1] = 0x00;
       mout[2] = 0x01;
       mout[3] = 0x01;
        break;
    default: // All other options (eg custom key): no flags
        mout[1] = 0x00;
        mout[2] = 0x00;
        mout[3] = 0x00;
    }

    if (k == 5) { // If indicate, flip flag and update value
        flgID = !flgID;
        mout[0] = flgID * 0x01;
        out << "Identify BUG! ID=" << flgID << Qt::endl;
    }
    else if (k == 6) {
        mout[0] = 0x10;
        out << "Reset BUG! to factory settings" << Qt::endl;
    }
    else
        mout[0] = 0x00;


    QByteArray output = QByteArray::fromRawData(mout,4);
    m_service->writeCharacteristic(infoChar, output, QLowEnergyService::WriteWithResponse);

    setInfo("Use mode updated.");
    emit dataChanged();

}

// Check if it is possible to fix lighter colours having black text on colour selection
// Add Indicate button

// EXTRA
// Add rotating BUG on splash
// Maybe: explode modes and be able to select specifc keys instead of presets


DeviceHandler::DeviceHandler(QObject *parent) :
    BluetoothBaseClass(parent)
{

}

void DeviceHandler::setAddressType(AddressType type)
{
    switch (type) {
    case DeviceHandler::AddressType::PublicAddress:
        m_addressType = QLowEnergyController::PublicAddress;
        break;
    case DeviceHandler::AddressType::RandomAddress:
        m_addressType = QLowEnergyController::RandomAddress;
        break;
    }
}

DeviceHandler::AddressType DeviceHandler::addressType() const
{
    if (m_addressType == QLowEnergyController::RandomAddress)
        return DeviceHandler::AddressType::RandomAddress;

    return DeviceHandler::AddressType::PublicAddress;
}

void DeviceHandler::setDevice(DeviceInfo *device)
{
    clearMessages();
    m_currentDevice = device;



    // Disconnect and delete old connection
    if (m_control) {
        m_control->disconnectFromDevice();
        delete m_control;
        m_control = nullptr;
    }

    // Create new controller and connect it if device available
    if (m_currentDevice) {

        // Make connections
        //! [Connect-Signals-1]
        m_control = QLowEnergyController::createCentral(m_currentDevice->getDevice(), this);
        //! [Connect-Signals-1]
        m_control->setRemoteAddressType(m_addressType);
        //! [Connect-Signals-2]
        connect(m_control, &QLowEnergyController::serviceDiscovered,
                this, &DeviceHandler::serviceDiscovered);
        connect(m_control, &QLowEnergyController::discoveryFinished,
                this, &DeviceHandler::serviceScanDone);

        connect(m_control, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
                this, [this](QLowEnergyController::Error error) {
            Q_UNUSED(error);
            setError("Cannot connect to remote device.");
        });
        connect(m_control, &QLowEnergyController::connected, this, [this]() {
            setInfo("Controller connected. Search services...");
            m_control->discoverServices();
        });
        connect(m_control, &QLowEnergyController::disconnected, this, [this]() {
            setError("LowEnergy controller disconnected");
        });

        // Connect
        m_control->connectToDevice();
        //! [Connect-Signals-2]
    }
}

void DeviceHandler::sendKeybind(QString value)
{
    out << "  Send keybind: " << value << Qt::endl;
    int output = 0x00;
    if (value == "Enter") output = 0xE0;
    else if (value == "←") output = 0xD8;
    else if (value == "↑") output = 0xDA;
    else if (value == "→") output = 0xD7;
    else if (value == "↓") output = 0xD9;
    else if (value == "Ctrl") output = 0x84;
    else if (value == "Alt") output = 0x86;
    else if (value == "Shift") output = 0x81;
    else if (value == "Escape") output = 0xB1;
    else if (value == "Space") output = 0x20;
    else { //convert to char and then to int
        QChar tc = value.at(0);
        tc = tc.toLower();
        out << "  Converted character: " << tc << Qt::endl;
        output = tc.toLatin1();
    }

    out << "  Converted integer:   " << output << Qt::endl;

    char chartmp[1];
    chartmp[0] = output;
    QByteArray number = QByteArray::fromRawData(chartmp,1);
    m_service->writeCharacteristic(bindChar, number, QLowEnergyService::WriteWithResponse);

    out << "Written keybind (sent: " << output << ")" << Qt::endl;
    setInfo("Key bind updated.");
    emit dataChanged();
}

void DeviceHandler::sendTimeout(QString value)
{
    // Convert value to int
    int toSend = value.toInt(NULL, 10);
    out << "Timer to send: " << toSend << Qt::endl;

    char charSend[2];
    charSend[0] = (toSend >> 8);
    out << "charSend[0] = " << int(charSend[0]) << Qt::endl;
    charSend[1] = (toSend);
    out << "charSend[1] = " << int(charSend[1]) << Qt::endl;

    QByteArray number;
    number = QByteArray::fromRawData(charSend,2);
    m_service->writeCharacteristic(timeoutChar, number, QLowEnergyService::WriteWithResponse);

    out << "Raw timeout send: " << number.toHex() << Qt::endl;
    setInfo("Timeout value updated.");

    __timeout = toSend;

    emit dataChanged();
}

void DeviceHandler::sendLayout()
{
    // fetch colour
    //int tmpcol;
    //tmpcol = 0xff0000; // temporary

    // fetch layout
    int tmplay = 0x00;
    tmplay = 8*__layout[3] + 4*__layout[2] + 2*__layout[1] + __layout[0];

    //uint tmp = (tmpcol << 8) + tmplay;
    QByteArray number;
    //number.setNum(tmp,16);

    // Split colour into R,G,B value

    char chartmp[4];
    chartmp[0] = (__colour & 0xff0000) >> 16;
    chartmp[1] = (__colour & 0x00ff00) >> 8;
    chartmp[2] = (__colour & 0x0000ff);
    chartmp[3] = tmplay;

    number = QByteArray::fromRawData(chartmp,4);

    //number.append(tmpcol);
    //number.fromRawData(tmp,2);
    m_service->writeCharacteristic(layoutChar, number, QLowEnergyService::WriteWithResponse);
    out << "Written layout (sent: " << number << ")" << Qt::endl;
    out << "     layout tmp (set: " << tmplay << ")" << Qt::endl;
    setInfo("Layout & colour updated.");
    emit dataChanged();
}

//! [Filter HeartRate service 1]
void DeviceHandler::serviceDiscovered(const QBluetoothUuid &gatt)
{
    //if (gatt == QBluetoothUuid(QBluetoothUuid::HeartRate)) {
    if (gatt == QBluetoothUuid(gattUUID)) {
        setInfo("Key bind service discovered. Waiting for service scan to be done...");
        m_foundGATTService = true;
        printf("UUID found! gatt == QBluetoothUuid(gattUUID)\n");
    }
}
//! [Filter HeartRate service 1]

void DeviceHandler::serviceScanDone()
{
    setInfo("Service scan done.");

    // Delete old service if available
    if (m_service) {
        delete m_service;
        m_service = nullptr;
    }

//! [Filter HeartRate service 2]
    // If heartRateService found, create new service
    if (m_foundGATTService)
        m_service = m_control->createServiceObject(QBluetoothUuid(gattUUID), this);

    if (m_service) {
        connect(m_service, &QLowEnergyService::stateChanged, this, &DeviceHandler::serviceStateChanged);
        //connect(m_service, &QLowEnergyService::characteristicChanged, this, &DeviceHandler::updateHeartRateValue);
        connect(m_service, &QLowEnergyService::descriptorWritten, this, &DeviceHandler::confirmedDescriptorWrite);
        m_service->discoverDetails();
        out << "m_service found!" << Qt::endl;
    } else {
        setError("Heart Rate Service not found.");
    }
//! [Filter HeartRate service 2]
}

// Service functions
//! [Find HRM characteristic]
void DeviceHandler::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    out << "Service changed!" << Qt::endl;
    switch (s) {
    case QLowEnergyService::DiscoveringServices:
        setInfo(tr("Discovering services...\n"));
        break;
    case QLowEnergyService::ServiceDiscovered:
    {
        setInfo(tr("Settings loaded."));
        bindChar = m_service->characteristic(QBluetoothUuid(bindUUID));
        layoutChar = m_service->characteristic(QBluetoothUuid(indcUUID));
        timeoutChar = m_service->characteristic(QBluetoothUuid(timeUUID));
        infoChar = m_service->characteristic(QBluetoothUuid(settUUID));
        if (!bindChar.isValid()) {
            printf("Binding characteristic not found.\n");
            break;
        }
        else {
            printf("Binding characteristic valid.\n");
        }
        if (!layoutChar.isValid()) {
            printf("Layout characteristic not found.\n");
            break;
        }
        else {
            printf("Layout characteristic valid.\n");
        }
        if (!timeoutChar.isValid()) {
            printf("Timeout characteristic not found.\n");
            break;
        }
        else {
            printf("Timeout characteristic valid.\n");
        }
        if (!infoChar.isValid()) {
            printf("Settings characteristic not found.\n");
            break;
        }
        else {
            printf("Settings characteristic valid.\n");
        }

        // This below is weird, but also key
//        m_bindingDesc = bindChar.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
//        if (m_bindingDesc.isValid())
//            printf("Binding data valid!\n");
////            m_service->writeDescriptor(m_bindingDesc, QByteArray::fromHex("0100"));
//        else
//            printf("Binding data invalid!\n");

//        QByteArray a = bindChar.value();
//        QString result;
//        if (a.isEmpty()) {
//            result = QStringLiteral("<none>");
//            out << "None" << Qt::endl;
//            break;
//        }
//        result = a;
//        result += QLatin1Char('\n');
//        result += a.toHex();

//        out << result << Qt::endl;

        break;
    }
    default:
        //nothing for now
        break;
    }

    emit aliveChanged();
}
//! [Find HRM characteristic]


void DeviceHandler::confirmedDescriptorWrite(const QLowEnergyDescriptor &d, const QByteArray &value)
{
    out << "Descriptor changed!" << Qt::endl;
    if (d.isValid() && d == m_bindingDesc && value == QByteArray::fromHex("0000")) {
        //disabled notifications -> assume disconnect intent
        m_control->disconnectFromDevice();
        delete m_service;
        m_service = nullptr;
    }
}

void DeviceHandler::disconnectService()
{
    m_foundGATTService = false;

    //disable notifications
    if (m_bindingDesc.isValid() && m_service
            && m_bindingDesc.value() == QByteArray::fromHex("0100")) {
        m_service->writeDescriptor(m_bindingDesc, QByteArray::fromHex("0000"));
    } else {
        if (m_control)
            m_control->disconnectFromDevice();

        delete m_service;
        m_service = nullptr;
    }
}

bool DeviceHandler::alive() const
{

    if (m_service)
        return m_service->state() == QLowEnergyService::ServiceDiscovered;

    return false;
}
