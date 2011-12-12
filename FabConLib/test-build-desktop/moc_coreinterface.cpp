/****************************************************************************
** Meta object code from reading C++ file 'coreinterface.h'
**
** Created: Mon Dec 12 15:37:08 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FabConLib/coreinterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coreinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CoreInterface[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      34,   32,   14,   14, 0x05,
      58,   56,   14,   14, 0x05,
      81,   75,   14,   14, 0x05,
     119,   14,   14,   14, 0x05,
     140,  128,   14,   14, 0x05,
     165,   14,   14,   14, 0x05,
     221,  204,   14,   14, 0x05,
     246,  242,   14,   14, 0x05,
     268,  266,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     311,  292,   14,   14, 0x0a,
     338,   14,   14,   14, 0x0a,
     353,   14,   14,   14, 0x0a,
     381,  369,   14,   14, 0x0a,
     417,  369,   14,   14, 0x0a,
     467,   14,  451,   14, 0x0a,
     493,  488,   14,   14, 0x0a,
     516,  510,   14,   14, 0x0a,
     540,  204,   14,   14, 0x0a,
     579,  561,   14,   14, 0x0a,
     611,   14,   14,   14, 0x0a,
     624,   14,   14,   14, 0x0a,
     637,   14,   14,   14, 0x0a,
     651,   14,   14,   14, 0x0a,
     665,   14,   14,   14, 0x0a,
     677,   14,   14,   14, 0x0a,
     692,  266,   14,   14, 0x0a,
     715,  266,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CoreInterface[] = {
    "CoreInterface\0\0outOfStateCall()\0l\0"
    "comPorts(QStringList)\0s\0stateChaged(int)\0"
    "x,y,z\0currentPosition(double,double,double)\0"
    "moving()\0time,volume\0estimated(double,double)\0"
    "materialsAvailable(QMap<int,Material>)\0"
    "bayid,materialid\0bayMaterial(int,int)\0"
    "cmd\0currentCommand(int)\0i\0"
    "needMaterialLoaded(int)\0configFile,comport\0"
    "setConfig(QString,QString)\0configLoaded()\0"
    "resetPosition()\0x,y,z,speed\0"
    "moveTo(double,double,double,double)\0"
    "move(double,double,double,double)\0"
    "QVector<double>\0getCurrentPosition()\0"
    "xdfl\0setXDFL(QString)\0bayid\0"
    "requestBayMaterial(int)\0setMaterial(int,int)\0"
    "bayid,amount,time\0moveBayMotor(int,double,double)\0"
    "startPrint()\0pausePrint()\0resumePrint()\0"
    "cancelPrint()\0forceStop()\0donePrinting()\0"
    "processingCommand(int)\0needMaterial(int)\0"
};

const QMetaObject CoreInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CoreInterface,
      qt_meta_data_CoreInterface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CoreInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CoreInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CoreInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CoreInterface))
        return static_cast<void*>(const_cast< CoreInterface*>(this));
    return QObject::qt_metacast(_clname);
}

int CoreInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: outOfStateCall(); break;
        case 1: comPorts((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: stateChaged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: currentPosition((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 4: moving(); break;
        case 5: estimated((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 6: materialsAvailable((*reinterpret_cast< QMap<int,Material>(*)>(_a[1]))); break;
        case 7: bayMaterial((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: currentCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: needMaterialLoaded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: setConfig((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: configLoaded(); break;
        case 12: resetPosition(); break;
        case 13: moveTo((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 14: move((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 15: { QVector<double> _r = getCurrentPosition();
            if (_a[0]) *reinterpret_cast< QVector<double>*>(_a[0]) = _r; }  break;
        case 16: setXDFL((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: requestBayMaterial((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: setMaterial((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: moveBayMotor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 20: startPrint(); break;
        case 21: pausePrint(); break;
        case 22: resumePrint(); break;
        case 23: cancelPrint(); break;
        case 24: forceStop(); break;
        case 25: donePrinting(); break;
        case 26: processingCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: needMaterial((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void CoreInterface::outOfStateCall()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CoreInterface::comPorts(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CoreInterface::stateChaged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CoreInterface::currentPosition(double _t1, double _t2, double _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CoreInterface::moving()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void CoreInterface::estimated(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CoreInterface::materialsAvailable(QMap<int,Material> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CoreInterface::bayMaterial(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CoreInterface::currentCommand(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CoreInterface::needMaterialLoaded(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
