/****************************************************************************
** Meta object code from reading C++ file 'virtualmachines.h'
**
** Created: Wed Nov 30 13:31:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FabConLib/virtualmachines.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'virtualmachines.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VMPrototype[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   13,   12,   12, 0x0a,
      46,   12,   41,   12, 0x0a,
      66,   12,   62,   12, 0x0a,
      88,   79,   12,   12, 0x0a,
     121,   12,  113,   12, 0x0a,
     138,  133,   41,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VMPrototype[] = {
    "VMPrototype\0\0comPort\0setComPort(QString)\0"
    "bool\0isInitialized()\0int\0nstatesize()\0"
    "document\0loadConfig(QDomDocument)\0"
    "QString\0getErrors()\0path\0executeNPath(NPath)\0"
};

const QMetaObject VMPrototype::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VMPrototype,
      qt_meta_data_VMPrototype, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VMPrototype::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VMPrototype::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VMPrototype::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VMPrototype))
        return static_cast<void*>(const_cast< VMPrototype*>(this));
    return QObject::qt_metacast(_clname);
}

int VMPrototype::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setComPort((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { bool _r = isInitialized();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { int _r = nstatesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: loadConfig((*reinterpret_cast< QDomDocument(*)>(_a[1]))); break;
        case 4: { QString _r = getErrors();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { bool _r = executeNPath((*reinterpret_cast< NPath(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
static const uint qt_meta_data_VirtualPrinter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   16,   15,   15, 0x0a,
      58,   15,   50,   15, 0x0a,
      80,   75,   70,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VirtualPrinter[] = {
    "VirtualPrinter\0\0document\0"
    "loadConfig(QDomDocument)\0QString\0"
    "getErrors()\0bool\0path\0executeNPath(NPath)\0"
};

const QMetaObject VirtualPrinter::staticMetaObject = {
    { &VMPrototype::staticMetaObject, qt_meta_stringdata_VirtualPrinter,
      qt_meta_data_VirtualPrinter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VirtualPrinter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VirtualPrinter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VirtualPrinter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VirtualPrinter))
        return static_cast<void*>(const_cast< VirtualPrinter*>(this));
    return VMPrototype::qt_metacast(_clname);
}

int VirtualPrinter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VMPrototype::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadConfig((*reinterpret_cast< QDomDocument(*)>(_a[1]))); break;
        case 1: { QString _r = getErrors();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { bool _r = executeNPath((*reinterpret_cast< NPath(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_TestPrinter[] = {

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
      22,   13,   12,   12, 0x0a,
      57,   52,   47,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TestPrinter[] = {
    "TestPrinter\0\0document\0loadConfig(QDomDocument)\0"
    "bool\0path\0executeNPath(NPath)\0"
};

const QMetaObject TestPrinter::staticMetaObject = {
    { &VMPrototype::staticMetaObject, qt_meta_stringdata_TestPrinter,
      qt_meta_data_TestPrinter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestPrinter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestPrinter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestPrinter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestPrinter))
        return static_cast<void*>(const_cast< TestPrinter*>(this));
    return VMPrototype::qt_metacast(_clname);
}

int TestPrinter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VMPrototype::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadConfig((*reinterpret_cast< QDomDocument(*)>(_a[1]))); break;
        case 1: { bool _r = executeNPath((*reinterpret_cast< NPath(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE