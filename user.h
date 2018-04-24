#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <fstream>
#include <QTextStream>
#include <string>
#include <QDebug>

#include "firebasehandler.h"

using namespace std;

class User
{
public:
    explicit User();
    bool signUp();
    bool login(QString email, QString password);
    bool exists(QString email, QString username);
    void addGameScore(int game, int score);
    QStringList getGame1Scores();
    QStringList getGame2Scores();
    QStringList getGame3Scores();
    int averageGlobalScore(int game);
    void storeData(QString firstName, QString lastName, QString email, QString username,
                   QString password, QString age, QString gender);

private:
    FirebaseHandler *fbh = new FirebaseHandler;
    QString firstName;
    QString lastName;
    QString email;
    QString username;
    QString password;
    QString age;
    QString gender;
};

extern User *user;

#endif // USER_H
