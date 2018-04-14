#ifndef FIREBASEHANDLER_H
#define FIREBASEHANDLER_H

#include <QObject>
#include <string.h>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>

using namespace std;
class FirebaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit FirebaseHandler(QObject *parent = 0);
    void signIn(QString email, QString password);
    void signUp(QString email, QString password);

private:
    QString urlSignIn, urlSignUp;

signals:

public slots:
    void replyFinished(QNetworkReply*);

};

#endif // FIREBASEHANDLER_H
