/****************************************************************************
** Meta object code from reading C++ file 'loadconfigthread.h'
**
** Created: Mon Dec 12 13:56:27 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../loadconfigthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loadconfigthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoadConfigThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      26,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoadConfigThread[] = {
    "LoadConfigThread\0\0ready()\0loaded()\0"
    "run()\0"
};

const QMetaObject LoadConfigThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_LoadConfigThread,
      qt_meta_data_LoadConfigThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoadConfigThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoadConfigThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoadConfigThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoadConfigThread))
        return static_cast<void*>(const_cast< LoadConfigThread*>(this));
    return QThread::qt_metacast(_clname);
}

int LoadConfigThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ready(); break;
        case 1: loaded(); break;
        case 2: run(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void LoadConfigThread::ready()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LoadConfigThread::loaded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
