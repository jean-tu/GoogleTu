/****************************************************************************
** Meta object code from reading C++ file 'multiwin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "multiwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multiwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Multiwin[] = {

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
      10,    9,    9,    9, 0x0a,
      30,    9,    9,    9, 0x0a,
      51,    9,    9,    9, 0x0a,
      68,    9,    9,    9, 0x0a,
      79,    9,    9,    9, 0x0a,
      88,    9,    9,    9, 0x0a,
      98,    9,    9,    9, 0x0a,
     107,    9,    9,    9, 0x0a,
     118,    9,    9,    9, 0x0a,
     129,    9,    9,    9, 0x0a,
     145,  140,    9,    9, 0x0a,
     177,  140,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Multiwin[] = {
    "Multiwin\0\0mainButtonClicked()\0"
    "otherButtonClicked()\0displayResults()\0"
    "fileSort()\0inSort()\0outSort()\0prSort()\0"
    "popFSort()\0popISort()\0popOSort()\0item\0"
    "changeInLists(QTreeWidgetItem*)\0"
    "changeOutLists(QTreeWidgetItem*)\0"
};

void Multiwin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Multiwin *_t = static_cast<Multiwin *>(_o);
        switch (_id) {
        case 0: _t->mainButtonClicked(); break;
        case 1: _t->otherButtonClicked(); break;
        case 2: _t->displayResults(); break;
        case 3: _t->fileSort(); break;
        case 4: _t->inSort(); break;
        case 5: _t->outSort(); break;
        case 6: _t->prSort(); break;
        case 7: _t->popFSort(); break;
        case 8: _t->popISort(); break;
        case 9: _t->popOSort(); break;
        case 10: _t->changeInLists((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 11: _t->changeOutLists((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Multiwin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Multiwin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Multiwin,
      qt_meta_data_Multiwin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Multiwin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Multiwin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Multiwin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Multiwin))
        return static_cast<void*>(const_cast< Multiwin*>(this));
    return QWidget::qt_metacast(_clname);
}

int Multiwin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
