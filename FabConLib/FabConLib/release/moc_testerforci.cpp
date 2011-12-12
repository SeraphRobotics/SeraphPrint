/****************************************************************************
** Meta object code from reading C++ file 'testerforci.h'
**
** Created: Mon Dec 12 15:23:25 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../testing/testerforci.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testerforci.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_testerforci[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      31,   25,   12,   12, 0x0a,
      75,   69,   12,   12, 0x0a,
      92,   12,   12,   12, 0x0a,
     105,  101,   12,   12, 0x0a,
     133,  130,   12,   12, 0x0a,
     189,  172,   12,   12, 0x0a,
     212,  210,   12,   12, 0x0a,
     234,  232,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_testerforci[] = {
    "testerforci\0\0setConfig()\0x,y,z\0"
    "updatedPosition(double,double,double)\0"
    "state\0chagedState(int)\0moving()\0t,v\0"
    "estimated(double,double)\0ms\0"
    "materialsAvailable(QMap<int,Material>)\0"
    "bayid,materialid\0bayMaterial(int,int)\0"
    "c\0currentCommand(int)\0i\0needMaterialLoaded(int)\0"
};

const QMetaObject testerforci::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_testerforci,
      qt_meta_data_testerforci, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &testerforci::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *testerforci::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *testerforci::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_testerforci))
        return static_cast<void*>(const_cast< testerforci*>(this));
    return QObject::qt_metacast(_clname);
}

int testerforci::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setConfig(); break;
        case 1: updatedPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: chagedState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: moving(); break;
        case 4: estimated((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: materialsAvailable((*reinterpret_cast< QMap<int,Material>(*)>(_a[1]))); break;
        case 6: bayMaterial((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: currentCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: needMaterialLoaded((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
