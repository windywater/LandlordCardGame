#-------------------------------------------------
#
# Project created by QtCreator 2014-12-14T13:21:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LandlordCardGame
TEMPLATE = app

RC_FILE = LandlordCardGame.rc

SOURCES += main.cpp\
        MainFrame.cpp \
    GamePanel.cpp \
    GameControl.cpp \
    MarkBoard.cpp \
    Player.cpp \
    Robot.cpp \
    UserPlayer.cpp \
    Cards.cpp \
    CardPic.cpp \
    Strategy.cpp \
    CallLordThread.cpp \
    PlayHandThread.cpp \
    Hand.cpp

HEADERS  += MainFrame.h \
    GamePanel.h \
    GameControl.h \
    MarkBoard.h \
    Player.h \
    Robot.h \
    UserPlayer.h \
    Cards.h \
    CardPic.h \
    Strategy.h \
    CallLordThread.h \
    PlayHandThread.h \
    Hand.h

FORMS    += MainFrame.ui \
    MarkBoard.ui

TRANSLATIONS += zh.ts

RESOURCES += \
    LandlordCardGame.qrc

OTHER_FILES += \
    zh.ts \
    LandlordCardGame.rc \
    stylesheet.qss

