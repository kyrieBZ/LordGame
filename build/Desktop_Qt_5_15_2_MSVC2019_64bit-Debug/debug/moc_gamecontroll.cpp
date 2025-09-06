/****************************************************************************
** Meta object code from reading C++ file 'gamecontroll.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../gamecontroll.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamecontroll.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameControll_t {
    QByteArrayData data[16];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameControll_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameControll_t qt_meta_stringdata_GameControll = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GameControll"
QT_MOC_LITERAL(1, 13, 19), // "playerStatusChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "Player*"
QT_MOC_LITERAL(4, 42, 6), // "player"
QT_MOC_LITERAL(5, 49, 12), // "PlayerStatus"
QT_MOC_LITERAL(6, 62, 6), // "status"
QT_MOC_LITERAL(7, 69, 17), // "notifyGrabLordBet"
QT_MOC_LITERAL(8, 87, 3), // "bet"
QT_MOC_LITERAL(9, 91, 4), // "flag"
QT_MOC_LITERAL(10, 96, 17), // "gameStatusChanged"
QT_MOC_LITERAL(11, 114, 10), // "GameStatus"
QT_MOC_LITERAL(12, 125, 14), // "notifyPlayHand"
QT_MOC_LITERAL(13, 140, 6), // "Cards&"
QT_MOC_LITERAL(14, 147, 5), // "cards"
QT_MOC_LITERAL(15, 153, 11) // "pendingInfo"

    },
    "GameControll\0playerStatusChanged\0\0"
    "Player*\0player\0PlayerStatus\0status\0"
    "notifyGrabLordBet\0bet\0flag\0gameStatusChanged\0"
    "GameStatus\0notifyPlayHand\0Cards&\0cards\0"
    "pendingInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameControll[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       7,    3,   44,    2, 0x06 /* Public */,
      10,    1,   51,    2, 0x06 /* Public */,
      12,    2,   54,    2, 0x06 /* Public */,
      15,    2,   59,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Bool,    4,    8,    9,
    QMetaType::Void, 0x80000000 | 11,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 13,    4,   14,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 13,    4,   14,

       0        // eod
};

void GameControll::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameControll *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playerStatusChanged((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< PlayerStatus(*)>(_a[2]))); break;
        case 1: _t->notifyGrabLordBet((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->gameStatusChanged((*reinterpret_cast< GameStatus(*)>(_a[1]))); break;
        case 3: _t->notifyPlayHand((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< Cards(*)>(_a[2]))); break;
        case 4: _t->pendingInfo((*reinterpret_cast< Player*(*)>(_a[1])),(*reinterpret_cast< Cards(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameControll::*)(Player * , PlayerStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControll::playerStatusChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameControll::*)(Player * , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControll::notifyGrabLordBet)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameControll::*)(GameStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControll::gameStatusChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GameControll::*)(Player * , Cards & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControll::notifyPlayHand)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GameControll::*)(Player * , Cards & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameControll::pendingInfo)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameControll::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GameControll.data,
    qt_meta_data_GameControll,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameControll::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameControll::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameControll.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameControll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GameControll::playerStatusChanged(Player * _t1, PlayerStatus _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameControll::notifyGrabLordBet(Player * _t1, int _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameControll::gameStatusChanged(GameStatus _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GameControll::notifyPlayHand(Player * _t1, Cards & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GameControll::pendingInfo(Player * _t1, Cards & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
