/****************************************************************************
** Meta object code from reading C++ file 'devicehandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../devicehandler.h"
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
    QByteArrayData data[30];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceHandler_t qt_meta_stringdata_DeviceHandler = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DeviceHandler"
QT_MOC_LITERAL(1, 14, 12), // "aliveChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "statsChanged"
QT_MOC_LITERAL(4, 41, 11), // "dataChanged"
QT_MOC_LITERAL(5, 53, 11), // "sendKeybind"
QT_MOC_LITERAL(6, 65, 5), // "value"
QT_MOC_LITERAL(7, 71, 11), // "sendTimeout"
QT_MOC_LITERAL(8, 83, 10), // "sendLayout"
QT_MOC_LITERAL(9, 94, 17), // "disconnectService"
QT_MOC_LITERAL(10, 112, 12), // "fetchBLEData"
QT_MOC_LITERAL(11, 125, 12), // "updateLayout"
QT_MOC_LITERAL(12, 138, 1), // "i"
QT_MOC_LITERAL(13, 140, 12), // "updateColour"
QT_MOC_LITERAL(14, 153, 8), // "from_gui"
QT_MOC_LITERAL(15, 162, 10), // "updateMode"
QT_MOC_LITERAL(16, 173, 1), // "k"
QT_MOC_LITERAL(17, 175, 7), // "keybind"
QT_MOC_LITERAL(18, 183, 8), // "getIDflg"
QT_MOC_LITERAL(19, 192, 6), // "colour"
QT_MOC_LITERAL(20, 199, 7), // "layout0"
QT_MOC_LITERAL(21, 207, 7), // "layout1"
QT_MOC_LITERAL(22, 215, 7), // "layout2"
QT_MOC_LITERAL(23, 223, 7), // "layout3"
QT_MOC_LITERAL(24, 231, 7), // "timeout"
QT_MOC_LITERAL(25, 239, 4), // "mode"
QT_MOC_LITERAL(26, 244, 11), // "addressType"
QT_MOC_LITERAL(27, 256, 11), // "AddressType"
QT_MOC_LITERAL(28, 268, 13), // "PublicAddress"
QT_MOC_LITERAL(29, 282, 13) // "RandomAddress"

    },
    "DeviceHandler\0aliveChanged\0\0statsChanged\0"
    "dataChanged\0sendKeybind\0value\0sendTimeout\0"
    "sendLayout\0disconnectService\0fetchBLEData\0"
    "updateLayout\0i\0updateColour\0from_gui\0"
    "updateMode\0k\0keybind\0getIDflg\0colour\0"
    "layout0\0layout1\0layout2\0layout3\0timeout\0"
    "mode\0addressType\0AddressType\0PublicAddress\0"
    "RandomAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
      10,   90, // properties
       1,  130, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   72,    2, 0x0a /* Public */,
       7,    1,   75,    2, 0x0a /* Public */,
       8,    0,   78,    2, 0x0a /* Public */,
       9,    0,   79,    2, 0x0a /* Public */,
      10,    0,   80,    2, 0x0a /* Public */,
      11,    1,   81,    2, 0x0a /* Public */,
      13,    1,   84,    2, 0x0a /* Public */,
      15,    1,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Int,   16,

 // properties: name, type, flags
      17, QMetaType::QString, 0x00495001,
      18, QMetaType::Bool, 0x00495001,
      19, QMetaType::Int, 0x00495001,
      20, QMetaType::Int, 0x00495001,
      21, QMetaType::Int, 0x00495001,
      22, QMetaType::Int, 0x00495001,
      23, QMetaType::Int, 0x00495001,
      24, QMetaType::Int, 0x00495001,
      25, QMetaType::QString, 0x00495001,
      26, 0x80000000 | 27, 0x0009510b,

 // properties: notify_signal_id
       2,
       2,
       2,
       2,
       2,
       2,
       2,
       2,
       2,
       0,

 // enums: name, alias, flags, count, data
      27,   27, 0x2,    2,  135,

 // enum data: key, value
      28, uint(DeviceHandler::AddressType::PublicAddress),
      29, uint(DeviceHandler::AddressType::RandomAddress),

       0        // eod
};

void DeviceHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->aliveChanged(); break;
        case 1: _t->statsChanged(); break;
        case 2: _t->dataChanged(); break;
        case 3: _t->sendKeybind((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sendTimeout((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sendLayout(); break;
        case 6: _t->disconnectService(); break;
        case 7: _t->fetchBLEData(); break;
        case 8: _t->updateLayout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->updateColour((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->updateMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceHandler::aliveChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceHandler::statsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DeviceHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceHandler::dataChanged)) {
                *result = 2;
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
        case 1: *reinterpret_cast< bool*>(_v) = _t->getIDflg(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->getColour(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->getLayout0(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->getLayout1(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->getLayout2(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->getLayout3(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->getTimeout(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->getTextMode(); break;
        case 9: *reinterpret_cast< AddressType*>(_v) = _t->addressType(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DeviceHandler *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 9: _t->setAddressType(*reinterpret_cast< AddressType*>(_v)); break;
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
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceHandler::aliveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeviceHandler::statsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DeviceHandler::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
