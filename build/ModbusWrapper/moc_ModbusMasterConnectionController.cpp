/****************************************************************************
** Meta object code from reading C++ file 'ModbusMasterConnectionController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../InternalLibraries/ModbusWrapper/ModbusMasterConnectionController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModbusMasterConnectionController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModbusMasterConnectionController_t {
    QByteArrayData data[10];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModbusMasterConnectionController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModbusMasterConnectionController_t qt_meta_stringdata_ModbusMasterConnectionController = {
    {
QT_MOC_LITERAL(0, 0, 32), // "ModbusMasterConnectionController"
QT_MOC_LITERAL(1, 33, 12), // "addRequester"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 13), // "ModbusRequest"
QT_MOC_LITERAL(4, 61, 13), // "modbusRequest"
QT_MOC_LITERAL(5, 75, 6), // "period"
QT_MOC_LITERAL(6, 82, 7), // "newData"
QT_MOC_LITERAL(7, 90, 10), // "ModbusData"
QT_MOC_LITERAL(8, 101, 4), // "data"
QT_MOC_LITERAL(9, 106, 12) // "slaveAddress"

    },
    "ModbusMasterConnectionController\0"
    "addRequester\0\0ModbusRequest\0modbusRequest\0"
    "period\0newData\0ModbusData\0data\0"
    "slaveAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModbusMasterConnectionController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       6,    2,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    8,    9,

       0        // eod
};

void ModbusMasterConnectionController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModbusMasterConnectionController *_t = static_cast<ModbusMasterConnectionController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addRequester((*reinterpret_cast< const ModbusRequest(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->newData((*reinterpret_cast< const ModbusData(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ModbusMasterConnectionController::*_t)(const ModbusRequest & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModbusMasterConnectionController::addRequester)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ModbusMasterConnectionController::*_t)(const ModbusData & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModbusMasterConnectionController::newData)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ModbusMasterConnectionController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModbusMasterConnectionController.data,
      qt_meta_data_ModbusMasterConnectionController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModbusMasterConnectionController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModbusMasterConnectionController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusMasterConnectionController.stringdata0))
        return static_cast<void*>(const_cast< ModbusMasterConnectionController*>(this));
    return QObject::qt_metacast(_clname);
}

int ModbusMasterConnectionController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ModbusMasterConnectionController::addRequester(const ModbusRequest & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModbusMasterConnectionController::newData(const ModbusData & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
