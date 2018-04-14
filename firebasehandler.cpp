#include "firebasehandler.h"

FirebaseHandler::FirebaseHandler(QObject *parent) :
    QObject(parent)
{
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

void FirebaseHandler::signUp(QString email, QString password) {
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
                         SLOT(replyFinished(QNetworkReply*)));
    QByteArray hi = "{email: \"" + email.toUtf8() +"\", password: \"" + password.toUtf8() + "\",returnSecureToken: true}";
    reply = manager->post(request, hi);
}

void FirebaseHandler::getScore(QString localId) {

}

void FirebaseHandler::replyFinished(QNetworkReply *reply)
{
    qDebug() << reply->readAll();
}
