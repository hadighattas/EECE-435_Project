#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <fstream>
#include <QTextStream>
#include <string>
#include <QDebug>

using namespace std;

class User
{
public:
    explicit User();
    bool signUp(QString firstName, QString lastName, QString email, QString username,
                QString password, QString age, QString gender);
    bool login(QString username, QString password);
    bool exists(QString email, QString username);
    void addGameScore(int game, int score);
    QStringList getGame1Scores();
    QStringList getGame2Scores();
    QStringList getGame3Scores();
    int averageGlobalScore(int game);

private:
    QString firstName;
    QString lastName;
    QString email;
    QString username;
    QString password;
    QString age;
    QString gender;
    QStringList game1Scores, game2Scores, game3Scores;
};

extern User *user;

#endif // USER_H
