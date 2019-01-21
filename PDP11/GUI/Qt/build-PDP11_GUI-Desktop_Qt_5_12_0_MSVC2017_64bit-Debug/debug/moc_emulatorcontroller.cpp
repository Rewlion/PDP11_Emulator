/****************************************************************************
** Meta object code from reading C++ file 'emulatorcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PDP11_GUI/emulatorcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emulatorcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EmulatorController_t {
    QByteArrayData data[12];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EmulatorController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EmulatorController_t qt_meta_stringdata_EmulatorController = {
    {
QT_MOC_LITERAL(0, 0, 18), // "EmulatorController"
QT_MOC_LITERAL(1, 19, 22), // "EmitUploadProgramToROM"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 10), // "pathToFile"
QT_MOC_LITERAL(4, 54, 8), // "EmitStep"
QT_MOC_LITERAL(5, 63, 7), // "EmitRun"
QT_MOC_LITERAL(6, 71, 18), // "uploadProgramToROM"
QT_MOC_LITERAL(7, 90, 4), // "step"
QT_MOC_LITERAL(8, 95, 3), // "run"
QT_MOC_LITERAL(9, 99, 4), // "stop"
QT_MOC_LITERAL(10, 104, 7), // "copyRom"
QT_MOC_LITERAL(11, 112, 9) // "RawRegion"

    },
    "EmulatorController\0EmitUploadProgramToROM\0"
    "\0pathToFile\0EmitStep\0EmitRun\0"
    "uploadProgramToROM\0step\0run\0stop\0"
    "copyRom\0RawRegion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EmulatorController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   59,    2, 0x0a /* Public */,
       7,    0,   62,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    0,   64,    2, 0x0a /* Public */,
      10,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 11,

       0        // eod
};

void EmulatorController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EmulatorController *_t = static_cast<EmulatorController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->EmitUploadProgramToROM((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->EmitStep(); break;
        case 2: _t->EmitRun(); break;
        case 3: _t->uploadProgramToROM((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->step(); break;
        case 5: _t->run(); break;
        case 6: _t->stop(); break;
        case 7: { RawRegion _r = _t->copyRom();
            if (_a[0]) *reinterpret_cast< RawRegion*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EmulatorController::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EmulatorController::EmitUploadProgramToROM)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EmulatorController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EmulatorController::EmitStep)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EmulatorController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EmulatorController::EmitRun)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EmulatorController::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_EmulatorController.data,
    qt_meta_data_EmulatorController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EmulatorController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmulatorController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EmulatorController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EmulatorController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void EmulatorController::EmitUploadProgramToROM(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EmulatorController::EmitStep()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void EmulatorController::EmitRun()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
