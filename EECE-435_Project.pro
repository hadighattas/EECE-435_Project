#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T16:02:00
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
TARGET = EECE-435_Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    welcomemenu.cpp \
    loginmenu.cpp \
    signupmenu.cpp \
    mainmenu.cpp \
    gametemplate.cpp \
    Game1/game1menu.cpp \
    Game1/game1scene.cpp \
    Game1/game1graphicsview.cpp \
    Game1/character.cpp \
    Game1/obstacle.cpp \
    Game1/obstaclegroup.cpp \
    Game1/global.cpp \
    Game1/game1score.cpp \
    user.cpp \
    Game2/game2menu.cpp \
    Game2/engineergraphicsview.cpp \
    Game2/engineerscene.cpp \
    Game2/firstsceneengineer.cpp \
    Game2/global2.cpp \
    Game2/randomalien.cpp \
    Game2/secondsceneengineer.cpp \
    Game2/thirdsceneengineer.cpp \
    Game2/fourthsceneengineer.cpp \
    Game2/fifthsceneengineer.cpp

HEADERS  += mainwindow.h \
    welcomemenu.h \
    loginmenu.h \
    signupmenu.h \
    mainmenu.h \
    gametemplate.h \
    Game1/game1menu.h \
    Game1/game1scene.h \
    Game1/game1graphicsview.h \
    Game1/character.h \
    Game1/obstacle.h \
    Game1/obstaclegroup.h \
    Game1/global.h \
    Game1/game1score.h \
    user.h \
    Game2/game2menu.h \
    Game2/engineergraphicsview.h \
    Game2/engineerscene.h \
    Game2/firstsceneengineer.h \
    Game2/global2.h \
    Game2/randomalien.h \
    Game2/secondsceneengineer.h \
    Game2/thirdsceneengineer.h \
    Game2/fourthsceneengineer.h \
    Game2/fifthsceneengineer.h

FORMS    += mainwindow.ui \
    welcomemenu.ui \
    loginmenu.ui \
    signupmenu.ui \
    mainmenu.ui \
    gametemplate.ui \
    Game1/game1menu.ui \
    Game1/game1score.ui \
    Game2/game2menu.ui
