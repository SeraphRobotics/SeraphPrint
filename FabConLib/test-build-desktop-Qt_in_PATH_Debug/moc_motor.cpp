/****************************************************************************
** Meta object code from reading C++ file 'motor.h'
**
** Created: Wed Nov 30 13:31:12 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../JrkerrElectronics/motor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'motor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Motor[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,    6,    7,    6, 0x0a,
      26,    6,   19,    6, 0x0a,
      42,   40,    6,    6, 0x0a,
      64,   62,    6,    6, 0x0a,
      88,    6,   19,    6, 0x0a,
     102,    6,   19,    6, 0x0a,
     120,    6,   19,    6, 0x0a,
     137,    6,   19,    6, 0x0a,
     154,    6,   19,    6, 0x0a,
     177,    6,   19,    6, 0x0a,
     194,    6,   19,    6, 0x0a,
     211,    6,   19,    6, 0x0a,
     232,    6,   19,    6, 0x0a,
     289,  258,  253,    6, 0x0a,
     360,  324,  253,    6, 0x0a,
     395,    6,    6,    6, 0x0a,
     406,    6,  253,    6, 0x0a,
     415,    6,  253,    6, 0x0a,
     430,    6,  422,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Motor[] = {
    "Motor\0\0int\0getID()\0double\0getPosition()\0"
    "v\0setVelocity(double)\0a\0setAcceleration(double)\0"
    "getVelocity()\0getAcceleration()\0"
    "getMinPosition()\0getMaxPosition()\0"
    "getCommandedPosition()\0getMinVelocity()\0"
    "getMaxVelocity()\0getMinAcceleration()\0"
    "getMaxAcceleration()\0bool\0"
    "position,velocity,acceleration\0"
    "moveAbsolute(double,double,double)\0"
    "positionDelta,velocity,acceleration\0"
    "moveRelative(double,double,double)\0"
    "waitMove()\0moving()\0stop()\0QString\0"
    "getErrors()\0"
};

const QMetaObject Motor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Motor,
      qt_meta_data_Motor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Motor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Motor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Motor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Motor))
        return static_cast<void*>(const_cast< Motor*>(this));
    return QObject::qt_metacast(_clname);
}

int Motor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { int _r = getID();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { double _r = getPosition();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 2: setVelocity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: setAcceleration((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: { double _r = getVelocity();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 5: { double _r = getAcceleration();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 6: { double _r = getMinPosition();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 7: { double _r = getMaxPosition();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 8: { double _r = getCommandedPosition();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 9: { double _r = getMinVelocity();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 10: { double _r = getMaxVelocity();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 11: { double _r = getMinAcceleration();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 12: { double _r = getMaxAcceleration();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 13: { bool _r = moveAbsolute((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = moveRelative((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: waitMove(); break;
        case 16: { bool _r = moving();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 17: { bool _r = stop();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: { QString _r = getErrors();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE