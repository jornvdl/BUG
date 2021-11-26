#include "devicehandler.h"
#include "ble_data.h"
#include "deviceinfo.h"
#include <QTextStream>
#include <QList>

int __keybind = 0x20;
bool __layout[4];
int __timeout = 300;
int __mode = 0;

QTextStream out(stdout);

// data
int BLE_Data::keybind() const
{
    return __keybind;
}

bool BLE_Data::layout(int i) const
{
    return __layout[i];
}

int BLE_Data::timeout() const
{
    return __timeout;
}

int BLE_Data::mode() const
{
    return __mode;
}

void BLE_Data::sendKeybind(int v)
{
    const char tmp = char(v);
    QByteArray number;
    //number.setNum(value,16);
    number.append(tmp);
    //number.fromRawData(tmp,2);
    m_service->writeCharacteristic(bindChar, number, QLowEnergyService::WriteWithResponse);
    out << "Written (int: " << number << ")" << Qt::endl;
    out << "  (not) (char: " << tmp << ")" << Qt::endl;
    setInfo("Key bind updated.");
    emit dataChanged();
}

void BLE_Data::sendLayout(int c, bool l[4])
{

}

void BLE_Data::sendTimeout(int t)
{

}

void BLE_Data::sendMode(int m)
{

}
