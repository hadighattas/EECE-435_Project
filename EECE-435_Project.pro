#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T16:02:00
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EECE-435_Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    welcomemenu.cpp \
    loginmenu.cpp \
    signupmenu.cpp \
    mainmenu.cpp \
    gametemplate.cpp \
    Game1/game1menu.cpp

HEADERS  += mainwindow.h \
    welcomemenu.h \
    loginmenu.h \
    signupmenu.h \
    mainmenu.h \
    gametemplate.h \
    Game1/game1menu.h

FORMS    += mainwindow.ui \
    welcomemenu.ui \
    loginmenu.ui \
    signupmenu.ui \
    mainmenu.ui \
    gametemplate.ui \
    Game1/game1menu.ui
