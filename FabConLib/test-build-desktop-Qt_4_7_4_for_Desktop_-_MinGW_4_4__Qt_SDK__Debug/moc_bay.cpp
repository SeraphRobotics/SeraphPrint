/****************************************************************************
** Meta object code from reading C++ file 'bay.h'
**
** Created: Mon Dec 12 15:39:02 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FabConLib/bay.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Bay[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x0a,
      24,    4,   19,    4, 0x0a,
      47,    4,   38,    4, 0x0a,
      70,   61,    4,    4, 0x0a,
     103,   98,   92,    4, 0x0a,
     126,  120,   92,    4, 0x0a,
     157,  145,   92,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Bay[] = {
    "Bay\0\0clearVolume()\0bool\0hasMaterial()\0"
    "Material\0getMaterial()\0material\0"
    "setMaterial(Material)\0NPath\0path\0"
    "onPath(XDFLPath)\0voxel\0onVoxel(XDFLVoxel)\0"
    "amount,time\0jogActuators(double,double)\0"
};

const QMetaObject Bay::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Bay,
      qt_meta_data_Bay, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Bay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Bay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Bay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Bay))
        return static_cast<void*>(const_cast< Bay*>(this));
    return QObject::qt_metacast(_clname);
}

int Bay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clearVolume(); break;
        case 1: { bool _r = hasMaterial();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { Material _r = getMaterial();
            if (_a[0]) *reinterpret_cast< Material*>(_a[0]) = _r; }  break;
        case 3: setMaterial((*reinterpret_cast< Material(*)>(_a[1]))); break;
        case 4: { NPath _r = onPath((*reinterpret_cast< XDFLPath(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NPath*>(_a[0]) = _r; }  break;
        case 5: { NPath _r = onVoxel((*reinterpret_cast< XDFLVoxel(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< NPath*>(_a[0]) = _r; }  break;
        case 6: { NPath _r = jogActuators((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< NPath*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
