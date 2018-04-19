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
    void signUp(QString firstName, QString lastName, QString email, QString username, QString password, QString age, QString gender);

private:
    QString urlSignIn, urlSignUp, urlUsers;

signals:

public slots:
    void replyFinished(QNetworkReply*);
    void addToDatabase(QNetworkReply*);

};

#endif // FIREBASEHANDLER_H
