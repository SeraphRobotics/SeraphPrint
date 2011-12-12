/****************************************************************************
** Meta object code from reading C++ file 'coordinatedmotion.h'
**
** Created: Mon Dec 12 15:39:25 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../JrkerrElectronics/coordinatedmotion.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coordinatedmotion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CoordinatedMotion[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   18,   19,   18, 0x0a,
      49,   18,   41,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CoordinatedMotion[] = {
    "CoordinatedMotion\0\0int\0getNumberOfAxes()\0"
    "QString\0getErrors()\0"
};

const QMetaObject CoordinatedMotion::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CoordinatedMotion,
      qt_meta_data_CoordinatedMotion, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CoordinatedMotion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CoordinatedMotion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CoordinatedMotion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CoordinatedMotion))
        return static_cast<void*>(const_cast< CoordinatedMotion*>(this));
    return QObject::qt_metacast(_clname);
}

int CoordinatedMotion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = getNumberOfAxes();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { QString _r = getErrors();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
