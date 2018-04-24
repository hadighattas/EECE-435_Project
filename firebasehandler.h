#ifndef FIREBASEHANDLER_H
#define FIREBASEHANDLER_H

#include <QObject>
#include <string.h>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QString>

#include <QJsonParseError>
#include <QVariant>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>

using namespace std;
class FirebaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit FirebaseHandler(QObject *parent = 0);
    void signIn(QString email, QString password);
    void signUp();
    void storeUserData(QString firstName, QString lastName, QString email,
                       QString username, QString password, QString age, QString gender);
    void getUserData();
    QStringList getInfo();
    QStringList getScore1();
    QStringList getScore2();
    QStringList getScore3();
    void addScore(int, int);
    void modifyGlobal(int game, int score);
    void getGlobalScores();
    int getGlobalScore(int game);

private:
    QString urlSignIn, urlSignUp, urlUsers, urlGlobal;
    QString firstName, lastName, username, age, gender, localId, email, password;
    QStringList score1, score2, score3;
    int avgScore1, avgScore2, avgScore3;
    int lastGamePlayed, lastScore;
    int called;
    bool done;

signals:
    void loginResult(bool);


public slots:
    void loginFinished(QNetworkReply*);
    void replyFinished(QNetworkReply*);
    void addToDatabase(QNetworkReply*);
    void replyGetData(QNetworkReply*);
    void putModifyGlobal(QNetworkReply*);
    void replyGetGlobalScores(QNetworkReply*);
};

#endif // FIREBASEHANDLER_H
