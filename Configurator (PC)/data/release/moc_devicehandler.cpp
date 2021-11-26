/****************************************************************************
** Meta object code from reading C++ file 'devicehandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../../Qt/heartrate-game/devicehandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devicehandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceHandler_t {
    QByteArrayData data[35];
    char stringdata0[343];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceHandler_t qt_meta_stringdata_DeviceHandler = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DeviceHandler"
QT_MOC_LITERAL(1, 14, 16), // "measuringChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 12), // "aliveChanged"
QT_MOC_LITERAL(4, 45, 12), // "statsChanged"
QT_MOC_LITERAL(5, 58, 11), // "dataChanged"
QT_MOC_LITERAL(6, 70, 16), // "startMeasurement"
QT_MOC_LITERAL(7, 87, 11), // "sendKeybind"
QT_MOC_LITERAL(8, 99, 5), // "value"
QT_MOC_LITERAL(9, 105, 10), // "sendLayout"
QT_MOC_LITERAL(10, 116, 15), // "stopMeasurement"
QT_MOC_LITERAL(11, 132, 17), // "disconnectService"
QT_MOC_LITERAL(12, 150, 12), // "fetchBLEData"
QT_MOC_LITERAL(13, 163, 12), // "updateLayout"
QT_MOC_LITERAL(14, 176, 1), // "i"
QT_MOC_LITERAL(15, 178, 7), // "keybind"
QT_MOC_LITERAL(16, 186, 6), // "colour"
QT_MOC_LITERAL(17, 193, 7), // "layout0"
QT_MOC_LITERAL(18, 201, 7), // "layout1"
QT_MOC_LITERAL(19, 209, 7), // "layout2"
QT_MOC_LITERAL(20, 217, 7), // "layout3"
QT_MOC_LITERAL(21, 225, 7), // "timeout"
QT_MOC_LITERAL(22, 233, 4), // "mode"
QT_MOC_LITERAL(23, 238, 9), // "measuring"
QT_MOC_LITERAL(24, 248, 5), // "alive"
QT_MOC_LITERAL(25, 254, 2), // "hr"
QT_MOC_LITERAL(26, 257, 5), // "maxHR"
QT_MOC_LITERAL(27, 263, 5), // "minHR"
QT_MOC_LITERAL(28, 269, 7), // "average"
QT_MOC_LITERAL(29, 277, 4), // "time"
QT_MOC_LITERAL(30, 282, 8), // "calories"
QT_MOC_LITERAL(31, 291, 11), // "addressType"
QT_MOC_LITERAL(32, 303, 11), // "AddressType"
QT_MOC_LITERAL(33, 315, 13), // "PublicAddress"
QT_MOC_LITERAL(34, 329, 13) // "RandomAddress"

    },
    "DeviceHandler\0measuringChanged\0\0"
    "aliveChanged\0statsChanged\0dataChanged\0"
    "startMeasurement\0sendKeybind\0value\0"
    "sendLayout\0stopMeasurement\0disconnectService\0"
    "fetchBLEData\0updateLayout\0i\0keybind\0"
    "colour\0layout0\0layout1\0layout2\0layout3\0"
    "timeout\0mode\0measuring\0alive\0hr\0maxHR\0"
    "minHR\0average\0time\0calories\0addressType\0"
    "AddressType\0PublicAddress\0RandomAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
      17,   84, // properties
       1,  152, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   73,    2, 0x0a /* Public */,
       7,    1,   74,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,
      12,    0,   80,    2, 0x0a /* Public */,
      13,    1,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

 // properties: name, type, flags
      15, QMetaType::QString, 0x00495001,
      16, QMetaType::Int, 0x00495001,
      17, QMetaType::Int, 0x00495001,
      18, QMetaType::Int, 0x00495001,
      19, QMetaType::Int, 0x00495001,
      20, QMetaType::Int, 0x00495001,
      21, QMetaType::Int, 0x00495001,
      22, QMetaType::Int, 0x00495001,
      23, QMetaType::Bool, 0x00495001,
      24, QMetaType::Bool, 0x00495001,
      25, QMetaType::Int, 0x00495001,
      26, QMetaType::Int, 0x00495001,
      27, QMetaType::Int, 0x00495001,
      28, QMetaType::Float, 0x00495001,
      29, QMetaType::Int, 0x00495001,
      30, QMetaType::Float, 0x00495001,
      31, 0x80000000 | 32, 0x0009510b,

 // properties: notify_signal_id
       3,
       3,
       3,
       3,
       3,
       3,
       3,
       3,
       0,
       1,
       2,
       2,
       0,
       2,
       2,
       2,
       0,

 // enums: name, alias, flags, count, data
      32,   32, 0x2,    2,  157,

 // enum data: key, value
      33, uint(DeviceHandler::AddressType::PublicAddress),
      34, uint(DeviceHandler::AddressType::RandomAddress),

       0        // eod
};

void DeviceHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->measuringChanged(); break;
        case 1: _t->aliveChanged(); break;
        case 2: _t->statsChanged(); break;
        case 3: _t->dataChanged(); break;
        case 4: _t->startMeasurement(); break;
        case 5: _t->sendKeybind((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sendLayout(); break;
        case 7: _t->stopMeasurement(); break;
        case 8: _t->disconnectService(); break;
        case 9: _t->fetchBLEData(); break;
        case 10: _t->updateLayout((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceHandler::measuringChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceHandler::aliveChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DeviceHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceHandler::statsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DeviceHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceHandler::dataChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DeviceHandler *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getKeybind(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getColour(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->getLayout0(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->getLayout1(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->getLayout2(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->getLayout3(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->getTimeout(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->getMode(); break;
        case 8: *reinterpret_cast< bool*>(_v) = _t->measuring(); break;
        case 9: *reinterpret_cast< bool*>(_v) = _t->alive(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->hr(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->maxHR(); break;
        case 12: *reinterpret_cast< int*>(_v) = _t->minHR(); break;
        case 13: *reinterpret_cast< float*>(_v) = _t->average(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->time(); break;
        case 15: *reinterpret_cast< float*>(_v) = _t->calories(); break;
        case 16: *reinterpret_cast< AddressType*>(_v) = _t->addressType(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DeviceHandler *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 16: _t->setAddressType(*reinterpret_cast< AddressType*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DeviceHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<BluetoothBaseClass::staticMetaObject>(),
    qt_meta_stringdata_DeviceHandler.data,
    qt_meta_data_DeviceHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DeviceHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceHandler.stringdata0))
        return static_cast<void*>(this);
    return BluetoothBaseClass::qt_metacast(_clname);
}

int DeviceHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BluetoothBaseClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 17;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceHandler::measuringChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeviceHandler::aliveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DeviceHandler::statsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DeviceHandler::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
