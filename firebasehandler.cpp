#include "firebasehandler.h"

FirebaseHandler::FirebaseHandler(QObject *parent) :
    QObject(parent)
{
    urlUsers = "https://aliens-vs-vices.firebaseio.com/users";
    urlGlobal = "https://aliens-vs-vices.firebaseio.com/global";
    urlSignIn = "https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key=AIzaSyCvP6AzTlc_nVkleSQjQHa9pGXrXVeM2fw";
    urlSignUp = "https://www.googleapis.com/identitytoolkit/v3/relyingparty/signupNewUser?key=AIzaSyCvP6AzTlc_nVkleSQjQHa9pGXrXVeM2fw";
    score1 = {};
    score2 = {};
    score3 = {};
    called = 1;

    done = false;
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
    //qDebug() << "Reply:" << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    QString localId = jsonObj["localId"].toString();
    this->localId = localId;
}

void FirebaseHandler::storeUserData(QString firstName, QString lastName, QString email, QString username, QString password, QString age, QString gender) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->username = username;
    this->age = age;
    this->gender = gender;
    this->email = email;
    this->password = password;
}

void FirebaseHandler::signUp() {
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

void FirebaseHandler::addToDatabase(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    qDebug() << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    QString localId = jsonObj["localId"].toString();
    this->localId = localId;

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
            + "\", \"age\": \"" + age.toUtf8() + "\", \"gender\": \"" + gender.toUtf8() + "\"}";
    qDebug() << "hi:" << hi;
    reply2 = manager->put(request, hi);
}

void FirebaseHandler::replyFinished(QNetworkReply *reply)
{
    QString strReply = (QString)reply->readAll();
    qDebug() << strReply;
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
    //qDebug() << strReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();

    QString item = localId;
    QJsonObject jsonObj2 = jsonObj[item].toObject();
    this->firstName = jsonObj2["first"].toString();
    this->lastName = jsonObj2["last"].toString();
    this->username = jsonObj2["username"].toString();
    this->age = jsonObj2["age"].toString();
    this->gender = jsonObj2["gender"].toString();

    this->score1 = jsonObj2["score1"].toString().split(",");
    if (this->score1.at(0) == "")
        this->score1.clear();
    this->score2 = jsonObj2["score2"].toString().split(",");
    if (this->score2.at(0) == "")
        this->score2.clear();
    this->score3 = jsonObj2["score3"].toString().split(",");
    if (this->score3.at(0) == "")
        this->score3.clear();

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
        called++;
        if (called % 2 == 0) {
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

        //qDebug() << "scoreList:" << scoreList;

        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request;
        QNetworkReply *reply = NULL;

        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        config.setProtocol(QSsl::TlsV1_2);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setHeader(QNetworkRequest::ServerHeader, "application/json");
        request.setSslConfiguration(config);

        QString url = urlUsers + "/" + this->localId + "/score" + QString::number(game) + ".json";
        request.setUrl(url);

        qDebug() << QString::number(called);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                             SLOT(replyFinished(QNetworkReply*)));
        QByteArray output;
        output.append("\"");
        output.append(scoreList.at(0));
        if (!(scoreList.size() == 1)) {
            scoreList.removeAt(0);
            foreach (const QString &str, scoreList)
            {
                output.append(",");
                output.append(str);
            }
        }
        output.append("\"");

        //Debug() << "scores:" << output;

        reply = manager->put(request, output);
        }
    }


    void FirebaseHandler::modifyGlobal(int game, int score) {
        lastGamePlayed = game;
        lastScore = score;

        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request;
        QNetworkReply *reply = NULL;

        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        config.setProtocol(QSsl::TlsV1_2);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setSslConfiguration(config);

        QString url = urlGlobal + "/score" + QString::number(game) + ".json";
        request.setUrl(url);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                             SLOT(putModifyGlobal(QNetworkReply*)));
        reply = manager->get(request);
    }

    void FirebaseHandler::putModifyGlobal(QNetworkReply *reply) {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();

        int average = jsonObj["average"].toInt();
        int count = jsonObj["count"].toInt();

        int newAverageInt = (average*count + lastScore)/(count+1);
        if (lastGamePlayed == 1)
            avgScore1 = newAverageInt;
        else if (lastGamePlayed == 2)
            avgScore2 = newAverageInt;
        else if (lastGamePlayed == 3)
            avgScore3 = newAverageInt;

        QString newAverage = QString::number(newAverageInt);
        QString newCount = QString::number(count+1);

        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request;
        QNetworkReply *reply2 = NULL;

        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        config.setProtocol(QSsl::TlsV1_2);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setSslConfiguration(config);

        QString url = urlGlobal + "/score" + QString::number(lastGamePlayed) + ".json";
        request.setUrl(url);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                             SLOT(replyFinished(QNetworkReply*)));
        QByteArray hi = "{\"average\":" + newAverage.toUtf8() + ",\"count\":" + newCount.toUtf8() + "}";
        reply2 = manager->put(request, hi);
    }

    void FirebaseHandler::getGlobalScores() {
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request;
        QNetworkReply *reply = NULL;

        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        config.setProtocol(QSsl::TlsV1_2);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setSslConfiguration(config);

        QString url = urlGlobal + ".json";
        request.setUrl(url);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                             SLOT(replyGetGlobalScores(QNetworkReply*)));
        reply = manager->get(request);
    }

    void FirebaseHandler::replyGetGlobalScores(QNetworkReply *reply) {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonResponse.object();

        QJsonObject score1 = jsonObj["score1"].toObject();
        QJsonObject score2 = jsonObj["score2"].toObject();
        QJsonObject score3 = jsonObj["score3"].toObject();

        avgScore1 = score1["average"].toInt();
        avgScore2 = score2["average"].toInt();
        avgScore3 = score3["average"].toInt();
    }

    int FirebaseHandler::getGlobalScore(int game) {
        if (game == 1)
            return avgScore1;
        else if (game == 2)
            return avgScore2;
        return avgScore3;
    }
