/****************************************************************************
** Meta object code from reading C++ file 'xdflhandler.h'
**
** Created: Wed Nov 30 13:31:08 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FabConLib/xdflhandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xdflhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XDFLHandler[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   40,   12,   12, 0x0a,
      74,   71,   12,   12, 0x0a,
     110,   12,   94,   12, 0x0a,
     132,  125,   12,   12, 0x0a,
     149,   12,  144,   12, 0x0a,
     167,  159,  144,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_XDFLHandler[] = {
    "XDFLHandler\0\0id\0needMaterialChange(int)\0"
    "node\0loadFromDom(QDomDocument)\0vm\0"
    "setVM(VMPrototype*)\0QList<Material>\0"
    "getMaterials()\0paused\0pause(bool)\0"
    "bool\0runXDFL()\0command\0runXDFL(QDomNode)\0"
};

const QMetaObject XDFLHandler::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_XDFLHandler,
      qt_meta_data_XDFLHandler, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XDFLHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XDFLHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XDFLHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XDFLHandler))
        return static_cast<void*>(const_cast< XDFLHandler*>(this));
    return QThread::qt_metacast(_clname);
}

int XDFLHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: needMaterialChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: loadFromDom((*reinterpret_cast< QDomDocument(*)>(_a[1]))); break;
        case 2: setVM((*reinterpret_cast< VMPrototype*(*)>(_a[1]))); break;
        case 3: { QList<Material> _r = getMaterials();
            if (_a[0]) *reinterpret_cast< QList<Material>*>(_a[0]) = _r; }  break;
        case 4: pause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: { bool _r = runXDFL();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = runXDFL((*reinterpret_cast< QDomNode(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void XDFLHandler::needMaterialChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
