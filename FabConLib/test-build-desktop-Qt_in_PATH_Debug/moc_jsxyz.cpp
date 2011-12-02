/****************************************************************************
** Meta object code from reading C++ file 'jsxyz.h'
**
** Created: Wed Nov 30 13:31:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FabConLib/jsxyz.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jsxyz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JsXYZ[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   20,    7,    6, 0x0a,
     107,   92,    7,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_JsXYZ[] = {
    "JsXYZ\0\0QScriptValue\0x,y,z,speed\0"
    "pathTo(QScriptValue,QScriptValue,QScriptValue,QScriptValue)\0"
    "JSPath,JSspeed\0pathAlong(QScriptValue,QScriptValue)\0"
};

const QMetaObject JsXYZ::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JsXYZ,
      qt_meta_data_JsXYZ, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JsXYZ::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JsXYZ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JsXYZ::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JsXYZ))
        return static_cast<void*>(const_cast< JsXYZ*>(this));
    return QObject::qt_metacast(_clname);
}

int JsXYZ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QScriptValue _r = pathTo((*reinterpret_cast< QScriptValue(*)>(_a[1])),(*reinterpret_cast< QScriptValue(*)>(_a[2])),(*reinterpret_cast< QScriptValue(*)>(_a[3])),(*reinterpret_cast< QScriptValue(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        case 1: { QScriptValue _r = pathAlong((*reinterpret_cast< QScriptValue(*)>(_a[1])),(*reinterpret_cast< QScriptValue(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
