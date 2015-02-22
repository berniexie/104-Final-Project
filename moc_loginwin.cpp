/****************************************************************************
** Meta object code from reading C++ file 'loginwin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lib/loginwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoginWin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,   30,   30,   30, 0x08,
      31,   30,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LoginWin[] = {
    "LoginWin\0create_new_account()\0\0"
    "check_acc_valid()\0"
};

void LoginWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoginWin *_t = static_cast<LoginWin *>(_o);
        switch (_id) {
        case 0: _t->create_new_account(); break;
        case 1: _t->check_acc_valid(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LoginWin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoginWin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LoginWin,
      qt_meta_data_LoginWin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWin))
        return static_cast<void*>(const_cast< LoginWin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LoginWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
