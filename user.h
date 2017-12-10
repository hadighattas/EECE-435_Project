#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <fstream>
#include <QTextStream>

using namespace std;

class User
{
public:
    explicit User();
    bool signUp(QString firstName, QString lastName, QString email, QString username,
                QString password, QString age, QString gender);
    bool login(QString username, QString password);
    bool exists(QString email, QString username);
    void addGame1Score(int score1);
    void addGame2Score(int score2);
    void addGame3Score(int score3);

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
