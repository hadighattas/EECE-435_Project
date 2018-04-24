#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T16:02:00
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

DEFINES += O0_EXPORT=
include(./OAuth/src/src.pri)

TARGET = EECE-435_Project
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    welcomemenu.cpp \
    loginmenu.cpp \
    signupmenu.cpp \
    mainmenu.cpp \
    Game1/game1menu.cpp \
    Game1/game1scene.cpp \
    Game1/game1graphicsview.cpp \
    Game1/character.cpp \
    Game1/obstacle.cpp \
    Game1/obstaclegroup.cpp \
    Game1/global.cpp \
    Game1/game1score.cpp \
    Game2/game2menu.cpp \
    Game2/Engineer/engineergraphicsview.cpp \
    Game2/Engineer/engineerscene.cpp \
    Game2/Engineer/firstsceneengineer.cpp \
    Game2/global2.cpp \
    Game2/randomalien.cpp \
    Game2/Engineer/secondsceneengineer.cpp \
    Game2/Engineer/thirdsceneengineer.cpp \
    Game2/Engineer/fourthsceneengineer.cpp \
    Game2/Engineer/fifthsceneengineer.cpp \
    Game2/Engineer/sixthsceneengineer.cpp \
    Game2/Engineer/seventhsceneengineer.cpp \
    Game2/Engineer/eigthsceneengineer.cpp \
    Game2/Doctor/doctorgraphicsview.cpp \
    Game2/Doctor/doctorscene.cpp \
    Game2/Doctor/firstscenedoctor.cpp \
    Game2/Doctor/secondscenedoctor.cpp \
    Game2/Doctor/thirdscenedoctor.cpp \
    Game2/Doctor/fourthscenedoctor.cpp \
    Game2/Doctor/fifthscenedoctor.cpp \
    Game2/Doctor/sixthscenedoctor.cpp \
    Game2/game2score.cpp \
    Game2/Doctor/seventhscenedoctor.cpp \
    Game3/game3menu.cpp \
    Game3/game3graphicsview.cpp \
    Game3/game3scene.cpp \
    Game3/global3.cpp \
    Game3/player.cpp \
    Game3/game3score.cpp\
    OAuth/fbdemo.cpp\
    OAuth/helper.cpp \
    globalindices.cpp \
    profile.cpp \
    firebasehandler.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    welcomemenu.h \
    loginmenu.h \
    signupmenu.h \
    mainmenu.h \
    Game1/game1menu.h \
    Game1/game1scene.h \
    Game1/game1graphicsview.h \
    Game1/character.h \
    Game1/obstacle.h \
    Game1/obstaclegroup.h \
    Game1/global.h \
    Game1/game1score.h \
    Game2/game2menu.h \
    Game2/Engineer/engineergraphicsview.h \
    Game2/Engineer/engineerscene.h \
    Game2/Engineer/firstsceneengineer.h \
    Game2/global2.h \
    Game2/randomalien.h \
    Game2/Engineer/secondsceneengineer.h \
    Game2/Engineer/thirdsceneengineer.h \
    Game2/Engineer/fourthsceneengineer.h \
    Game2/Engineer/fifthsceneengineer.h \
    Game2/Engineer/sixthsceneengineer.h \
    Game2/Engineer/seventhsceneengineer.h \
    Game2/Engineer/eigthsceneengineer.h \
    Game2/Doctor/doctorgraphicsview.h \
    Game2/Doctor/doctorscene.h \
    Game2/Doctor/firstscenedoctor.h \
    Game2/Doctor/secondscenedoctor.h \
    Game2/Doctor/thirdscenedoctor.h \
    Game2/Doctor/fourthscenedoctor.h \
    Game2/Doctor/fifthscenedoctor.h \
    Game2/Doctor/sixthscenedoctor.h \
    Game2/game2score.h \
    Game2/Doctor/seventhscenedoctor.h \
    Game3/game3menu.h \
    Game3/game3graphicsview.h \
    Game3/game3scene.h \
    Game3/global3.h \
    Game3/player.h \
    Game3/game3score.h \
    OAuth/fbdemo.h\
    OAuth/helper.h \
    globalindices.h \
    profile.h \
    firebasehandler.h \
    user.h

FORMS    += mainwindow.ui \
    welcomemenu.ui \
    loginmenu.ui \
    signupmenu.ui \
    mainmenu.ui \
    Game1/game1menu.ui \
    Game1/game1score.ui \
    Game2/game2menu.ui \
    Game2/game2score.ui \
    Game3/game3menu.ui \
    Game3/game3score.ui \
    profile.ui

RESOURCES += \
    resources.qrc
