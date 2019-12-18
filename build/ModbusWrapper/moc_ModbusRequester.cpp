/****************************************************************************
** Meta object code from reading C++ file 'ModbusRequester.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../InternalLibraries/ModbusWrapper/ModbusRequester.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModbusRequester.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModbusRequester_t {
    QByteArrayData data[9];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModbusRequester_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModbusRequester_t qt_meta_stringdata_ModbusRequester = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ModbusRequester"
QT_MOC_LITERAL(1, 16, 7), // "newTask"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 14), // "ModbusRequest*"
QT_MOC_LITERAL(4, 40, 13), // "modbusRequest"
QT_MOC_LITERAL(5, 54, 7), // "newData"
QT_MOC_LITERAL(6, 62, 10), // "ModbusData"
QT_MOC_LITERAL(7, 73, 4), // "data"
QT_MOC_LITERAL(8, 78, 12) // "slaveAddress"

    },
    "ModbusRequester\0newTask\0\0ModbusRequest*\0"
    "modbusRequest\0newData\0ModbusData\0data\0"
    "slaveAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModbusRequester[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,
       5,    2,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,

       0        // eod
};

void ModbusRequester::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModbusRequester *_t = static_cast<ModbusRequester *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newTask((*reinterpret_cast< ModbusRequest*(*)>(_a[1]))); break;
        case 1: _t->newData((*reinterpret_cast< const ModbusData(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ModbusRequester::*_t)(ModbusRequest * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModbusRequester::newTask)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ModbusRequester::*_t)(const ModbusData & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModbusRequester::newData)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ModbusRequester::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModbusRequester.data,
      qt_meta_data_ModbusRequester,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModbusRequester::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModbusRequester::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModbusRequester.stringdata0))
        return static_cast<void*>(const_cast< ModbusRequester*>(this));
    return QObject::qt_metacast(_clname);
}

int ModbusRequester::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ModbusRequester::newTask(ModbusRequest * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModbusRequester::newData(const ModbusData & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
