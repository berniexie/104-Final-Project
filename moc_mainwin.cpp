/****************************************************************************
** Meta object code from reading C++ file 'mainwin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lib/mainwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,   19,   19,   19, 0x08,
      20,   19,   19,   19, 0x08,
      32,   19,   19,   19, 0x08,
      43,   70,   19,   19, 0x08,
      75,   70,   19,   19, 0x08,
     103,   19,   19,   19, 0x08,
     115,   19,   19,   19, 0x08,
     128,   19,   19,   19, 0x08,
     144,  170,   19,   19, 0x08,
     185,  170,   19,   19, 0x08,
     220,  242,   19,   19, 0x08,
     248,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWin[] = {
    "MainWin\0doSearch()\0\0andSearch()\0"
    "orSearch()\0openLink(QListWidgetItem*)\0"
    "item\0adClicked(QListWidgetItem*)\0"
    "showAbout()\0sort_alpha()\0sort_pagerank()\0"
    "PageRank(mySet<WebPage*>)\0search_results\0"
    "Expanded_Results(mySet<WebPage*>&)\0"
    "print_results(string)\0ofile\0print_clicks()\0"
};

void MainWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWin *_t = static_cast<MainWin *>(_o);
        switch (_id) {
        case 0: _t->doSearch(); break;
        case 1: _t->andSearch(); break;
        case 2: _t->orSearch(); break;
        case 3: _t->openLink((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->adClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->showAbout(); break;
        case 6: _t->sort_alpha(); break;
        case 7: _t->sort_pagerank(); break;
        case 8: _t->PageRank((*reinterpret_cast< mySet<WebPage*>(*)>(_a[1]))); break;
        case 9: _t->Expanded_Results((*reinterpret_cast< mySet<WebPage*>(*)>(_a[1]))); break;
        case 10: _t->print_results((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 11: _t->print_clicks(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWin,
      qt_meta_data_MainWin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWin))
        return static_cast<void*>(const_cast< MainWin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
