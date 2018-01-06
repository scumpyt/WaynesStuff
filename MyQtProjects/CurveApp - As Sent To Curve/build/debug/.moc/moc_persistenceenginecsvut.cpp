/****************************************************************************
** Meta object code from reading C++ file 'persistenceenginecsvut.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../UnitTests/persistenceenginecsvut.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'persistenceenginecsvut.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PersistenceEngineCSVUT_t {
    QByteArrayData data[14];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PersistenceEngineCSVUT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PersistenceEngineCSVUT_t qt_meta_stringdata_PersistenceEngineCSVUT = {
    {
QT_MOC_LITERAL(0, 0, 22), // "PersistenceEngineCSVUT"
QT_MOC_LITERAL(1, 23, 12), // "initTestCase"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4), // "init"
QT_MOC_LITERAL(4, 42, 7), // "cleanup"
QT_MOC_LITERAL(5, 50, 15), // "cleanupTestCase"
QT_MOC_LITERAL(6, 66, 16), // "testCreateNewLog"
QT_MOC_LITERAL(7, 83, 19), // "testOpenExistingLog"
QT_MOC_LITERAL(8, 103, 13), // "testDeleteLog"
QT_MOC_LITERAL(9, 117, 13), // "testLogExists"
QT_MOC_LITERAL(10, 131, 17), // "testWriteVehicles"
QT_MOC_LITERAL(11, 149, 15), // "testWriteEvents"
QT_MOC_LITERAL(12, 165, 16), // "testReadVehicles"
QT_MOC_LITERAL(13, 182, 14) // "testReadEvents"

    },
    "PersistenceEngineCSVUT\0initTestCase\0"
    "\0init\0cleanup\0cleanupTestCase\0"
    "testCreateNewLog\0testOpenExistingLog\0"
    "testDeleteLog\0testLogExists\0"
    "testWriteVehicles\0testWriteEvents\0"
    "testReadVehicles\0testReadEvents"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PersistenceEngineCSVUT[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PersistenceEngineCSVUT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PersistenceEngineCSVUT *_t = static_cast<PersistenceEngineCSVUT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->init(); break;
        case 2: _t->cleanup(); break;
        case 3: _t->cleanupTestCase(); break;
        case 4: _t->testCreateNewLog(); break;
        case 5: _t->testOpenExistingLog(); break;
        case 6: _t->testDeleteLog(); break;
        case 7: _t->testLogExists(); break;
        case 8: _t->testWriteVehicles(); break;
        case 9: _t->testWriteEvents(); break;
        case 10: _t->testReadVehicles(); break;
        case 11: _t->testReadEvents(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PersistenceEngineCSVUT::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PersistenceEngineCSVUT.data,
      qt_meta_data_PersistenceEngineCSVUT,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PersistenceEngineCSVUT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersistenceEngineCSVUT::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PersistenceEngineCSVUT.stringdata0))
        return static_cast<void*>(const_cast< PersistenceEngineCSVUT*>(this));
    return QObject::qt_metacast(_clname);
}

int PersistenceEngineCSVUT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
