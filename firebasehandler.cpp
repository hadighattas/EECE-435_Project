#include "firebasehandler.h"

FirebaseHandler::FirebaseHandler(QObject *parent) :
    QObject(parent)
{
    urlUsers = "https://aliens-vs-vices.firebaseio.com/users";
    urlSignIn = "https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key=AIzaSyCvP6AzTlc_nVkleSQjQHa9pGXrXVeM2fw";
    urlSignUp = "https://www.googleapis.com/identitytoolkit/v3/relyingparty/signupNewUser?key=AIzaSyCvP6AzTlc_nVkleSQjQHa9pGXrXVeM2fw";
}

void FirebaseHandler::signIn(QString email, QString password){
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *reply = NULL;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");
    request.setSslConfiguration(config);
    request.setUrl(urlSignIn);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                         SLOT(loginFinished(QNetworkReply*)));
    QByteArray hi = "{email: \"" + email.toUtf8() + "\",password: \"" + password.toUtf8() + "\",returnSecureToken: true}";
    reply = manager->post(request, hi);
}

void FirebaseHandler::loginFinished(QNetworkReply* reply) {
    QString strReply = (QString)reply->readAll();
    qDebug() << "Reply:" << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    QString localId = jsonObj["localId"].toString();
    qDebug() << "localId:" << localId;
    this->localId = localId;
}


void FirebaseHandler::signUp(QString firstName, QString lastName, QString email, QString username,
                             QString password, QString age, QString gender) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->username = username;
    this->age = age;
    this->gender = gender;
    this->score1 = {};
    this->score2 = {};
    this->score3 = {};

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *reply = NULL;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");
    request.setSslConfiguration(config);

    request.setUrl(urlSignUp);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                         SLOT(addToDatabase(QNetworkReply*)));
    QByteArray hi = "{email: \"" + email.toUtf8() +"\", password: \"" + password.toUtf8() + "\",returnSecureToken: true}";
    reply = manager->post(request, hi);
}

//void FirebaseHandler::getScore(QString localId) {

//}


void FirebaseHandler::addToDatabase(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    qDebug() << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    QString localId = jsonObj["localId"].toString();
    qDebug() << "localId" << localId;

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *reply2 = NULL;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);

    QString url = urlUsers + "/" + localId + ".json";
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                         SLOT(replyFinished(QNetworkReply*)));
    QByteArray hi = "{\"first\": \"" + firstName.toUtf8() + "\", \"last\": \"" + lastName.toUtf8() + "\", \"username\": \"" + username.toUtf8()
            + "\", \"age\": \"" + age.toUtf8() + "\", \"gender\": \"" + gender.toUtf8() + "\", \"score1\": \"0\", \"score2\": \"0\", \"score3\": \"0\"}";
    reply2 = manager->put(request, hi);
}

void FirebaseHandler::replyFinished(QNetworkReply *reply)
{
//    QString strReply = (QString)reply->readAll();
//    qDebug() << strReply;
//    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
//    QJsonObject jsonObj = jsonResponse.object();
//    QString localId = jsonObj["localId"].toString();
//    qDebug() << "localId" << localId;
//    this->localId = localId;
}

void FirebaseHandler::getUserData() {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *reply = NULL;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");
    request.setSslConfiguration(config);

    QString url = urlUsers + "/" + localId + ".json";
    request.setUrl(url);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                         SLOT(replyGetData(QNetworkReply*)));
    reply = manager->get(request);
}

void FirebaseHandler::replyGetData(QNetworkReply *reply) {
    QString strReply = (QString)reply->readAll();
    qDebug() << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();

    QString item = localId;
    qDebug() << "item:" << item;
    QJsonObject jsonObj2 = jsonObj[item].toObject();
    this->firstName = jsonObj2["first"].toString();
    this->lastName = jsonObj2["last"].toString();
    this->username = jsonObj2["username"].toString();
    this->age = jsonObj2["age"].toString();
    this->gender = jsonObj2["gender"].toString();

    QJsonObject jsonObj3 = jsonObj2["score1"].toObject();
    score1.append(jsonObj3["0"].toString());
    qDebug() << "score1:" << score1;
//    array = jsonObj2["score2"].toArray();
//    foreach (const QJsonValue & value, array) {
//        score2.append(value.toString());
//    }
//    array = jsonObj2["score3"].toArray();
//    foreach (const QJsonValue & value, array) {
//        score3.append(value.toString());
//    }
}

QStringList FirebaseHandler::getInfo() {
    QStringList info = {firstName, lastName, username, age, gender};
    return info;
}

QStringList FirebaseHandler::getScore1() {
    return score1;
}

    QStringList FirebaseHandler::getScore2() {
        return score2;
    }

    QStringList FirebaseHandler::getScore3() {
        return score3;
    }

    void FirebaseHandler::addScore(int game, int score) {
        QString scoreString = QString::number(score);

        QStringList scoreList;
        if (game == 1){
            score1.append(scoreString);
            scoreList = score1;
        }
        else if (game == 2){
            score2.append(scoreString);
            scoreList = score2;
        }
        else {
            score3.append(scoreString);
            scoreList = score3;
        }

        qDebug() << "scoreList:" << scoreList;

        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request;
        QNetworkReply *reply = NULL;

        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        config.setProtocol(QSsl::TlsV1_2);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setSslConfiguration(config);

        qDebug() << "localId2:" << localId;
        QString url = urlUsers + "/" + this->localId + "/score" + QString::number(game) + ".json";
        qDebug() << "url:" << url;
        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::ServerHeader, "application/json");
        connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                             SLOT(replyFinished(QNetworkReply*)));
        QByteArray output;
        output = "[";
        foreach (const QString &str, scoreList)
        {
            output.append(str);
            output.append(",");
        }
        output.remove(-1, 1);
        output.append("]");

        qDebug() << "scores:" << output;

        reply = manager->put(request, output);
    }
