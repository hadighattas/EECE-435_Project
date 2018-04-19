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
    request.setSslConfiguration(config);
    request.setUrl(urlSignIn);
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                         SLOT(replyFinished(QNetworkReply*)));
    QByteArray hi = "{email: \"" + email.toUtf8() + "\", password: \"" + password.toUtf8() + "\",returnSecureToken: true}";
    reply = manager->post(request, hi);
}

void FirebaseHandler::signUp(QString firstName, QString lastName, QString email, QString username,
                             QString password, QString age, QString gender) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply *reply = NULL;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setSslConfiguration(config);
    request.setUrl(urlSignUp);
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");
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

    request.setSslConfiguration(config);
    urlUsers += "/" + localId + ".json";
    request.setUrl(urlUsers);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,
                         SLOT(replyFinished(QNetworkReply*)));
//    QByteArray hi = "{\"first\": \"" + firstName.toUtf8() + "\", \"last\": \"" + lastName.toUtf8() + "\"}";
//    reply2 = manager->put(request, hi);
}

void FirebaseHandler::replyFinished(QNetworkReply *reply)
{

}
