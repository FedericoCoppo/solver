/****************************************************************************
** Meta object code from reading C++ file 'I64SpinBox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../I64SpinBox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'I64SpinBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_I64QSpinBox_t {
    QByteArrayData data[9];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_I64QSpinBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_I64QSpinBox_t qt_meta_stringdata_I64QSpinBox = {
    {
QT_MOC_LITERAL(0, 0, 11), // "I64QSpinBox"
QT_MOC_LITERAL(1, 12, 12), // "valueChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 1), // "i"
QT_MOC_LITERAL(4, 28, 12), // "I64QSpinBox*"
QT_MOC_LITERAL(5, 41, 2), // "pt"
QT_MOC_LITERAL(6, 44, 4), // "text"
QT_MOC_LITERAL(7, 49, 8), // "setValue"
QT_MOC_LITERAL(8, 58, 5) // "value"

    },
    "I64QSpinBox\0valueChanged\0\0i\0I64QSpinBox*\0"
    "pt\0text\0setValue\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_I64QSpinBox[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    8,

       0        // eod
};

void I64QSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<I64QSpinBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< qlonglong(*)>(_a[1])),(*reinterpret_cast< I64QSpinBox*(*)>(_a[2]))); break;
        case 1: _t->valueChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setValue((*reinterpret_cast< qlonglong(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< I64QSpinBox* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (I64QSpinBox::*)(qlonglong , I64QSpinBox * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I64QSpinBox::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (I64QSpinBox::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&I64QSpinBox::valueChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject I64QSpinBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractSpinBox::staticMetaObject>(),
    qt_meta_stringdata_I64QSpinBox.data,
    qt_meta_data_I64QSpinBox,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *I64QSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *I64QSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_I64QSpinBox.stringdata0))
        return static_cast<void*>(this);
    return QAbstractSpinBox::qt_metacast(_clname);
}

int I64QSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void I64QSpinBox::valueChanged(qlonglong _t1, I64QSpinBox * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void I64QSpinBox::valueChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
