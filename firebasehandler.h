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
    void signUp(QString firstName, QString lastName, QString email, QString username,
                QString password, QString age, QString gender);
    void getUserData();
    QStringList getInfo();
    QStringList getScore1();
    QStringList getScore2();
    QStringList getScore3();
    void addScore(int, int);

private:
    QString urlSignIn, urlSignUp, urlUsers;
    QString firstName, lastName, username, age, gender, localId;
    QStringList score1, score2, score3;

signals:

public slots:
    void loginFinished(QNetworkReply*);
    void replyFinished(QNetworkReply*);
    void addToDatabase(QNetworkReply*);
    void replyGetData(QNetworkReply*);

};

#endif // FIREBASEHANDLER_H
