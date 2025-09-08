QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animationwindow.cpp \
    bgm_controll.cpp \
    buttongroup.cpp \
    card.cpp \
    cardpanel.cpp \
    cards.cpp \
    countdown.cpp \
    endingpanel.cpp \
    gamecontroll.cpp \
    loading.cpp \
    main.cpp \
    gamepanel.cpp \
    mybutton.cpp \
    player.cpp \
    playhand.cpp \
    robot.cpp \
    robotgrablord.cpp \
    robotplayhand.cpp \
    scorepanel.cpp \
    strategy.cpp \
    userplayer.cpp

HEADERS += \
    animationwindow.h \
    bgm_controll.h \
    buttongroup.h \
    card.h \
    cardpanel.h \
    cards.h \
    countdown.h \
    endingpanel.h \
    gamecontroll.h \
    gamepanel.h \
    loading.h \
    mybutton.h \
    player.h \
    playhand.h \
    robot.h \
    robotgrablord.h \
    robotplayhand.h \
    scorepanel.h \
    strategy.h \
    userplayer.h

FORMS += \
    buttongroup.ui \
    gamepanel.ui \
    scorepanel.ui

TRANSLATIONS += \
    LandLords_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

#图标
RC_ICONS = images/logo.ico
