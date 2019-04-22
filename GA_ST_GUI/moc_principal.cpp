/****************************************************************************
** Meta object code from reading C++ file 'principal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "principal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'principal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Principal_t {
    QByteArrayData data[10];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Principal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Principal_t qt_meta_stringdata_Principal = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Principal"
QT_MOC_LITERAL(1, 10, 32), // "on_cmb_grafo_currentIndexChanged"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 4), // "arg1"
QT_MOC_LITERAL(4, 49, 33), // "on_chk_previsualizar_stateCha..."
QT_MOC_LITERAL(5, 83, 22), // "on_btn_iniciar_pressed"
QT_MOC_LITERAL(6, 106, 25), // "on_txt_random_textChanged"
QT_MOC_LITERAL(7, 132, 23), // "on_act_fechar_triggered"
QT_MOC_LITERAL(8, 156, 22), // "on_act_sobre_triggered"
QT_MOC_LITERAL(9, 179, 30) // "on_act_abrir_solucao_triggered"

    },
    "Principal\0on_cmb_grafo_currentIndexChanged\0"
    "\0arg1\0on_chk_previsualizar_stateChanged\0"
    "on_btn_iniciar_pressed\0on_txt_random_textChanged\0"
    "on_act_fechar_triggered\0on_act_sobre_triggered\0"
    "on_act_abrir_solucao_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Principal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    0,   52,    2, 0x08 /* Private */,
       5,    0,   53,    2, 0x08 /* Private */,
       6,    1,   54,    2, 0x08 /* Private */,
       7,    0,   57,    2, 0x08 /* Private */,
       8,    0,   58,    2, 0x08 /* Private */,
       9,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Principal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Principal *_t = static_cast<Principal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cmb_grafo_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_chk_previsualizar_stateChanged(); break;
        case 2: _t->on_btn_iniciar_pressed(); break;
        case 3: _t->on_txt_random_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_act_fechar_triggered(); break;
        case 5: _t->on_act_sobre_triggered(); break;
        case 6: _t->on_act_abrir_solucao_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Principal::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Principal.data,
      qt_meta_data_Principal,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Principal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Principal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Principal.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Principal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
