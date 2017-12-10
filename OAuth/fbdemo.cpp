

#include "fbdemo.h"
#include "o0globals.h"
#include "o0settingsstore.h"

const char FB_APP_KEY[] = "571523936513739";
const char FB_APP_SECRET[] = "e600cd4fcfd8b3015e3f38543785c987";

const char FB_REQUEST_URL[] = "https://www.facebook.com/dialog/oauth";
const char FB_DEBUG_TOKEN[] = "https://graph.facebook.com/me?fields=id&access_token=%1";
const char FB_REQUEST_SCOPE[] = "email,user_birthday";
const char FbGraph[] = "https://graph.facebook.com/me?fields=first_name,last_name,email,birthday,gender";

const int localPort = 8000;

#define QENUM_NAME(o,e,v) (o::staticMetaObject.enumerator(o::staticMetaObject.indexOfEnumerator(#e)).valueToKey((v)))
#define GRANTFLOW_STR(v) QString(QENUM_NAME(O2, GrantFlow, v))

FBDemo::FBDemo(QObject *parent) :
    QObject(parent) {
    o2Facebook_ = new O2Facebook(this);

    o2Facebook_->setClientId(FB_APP_KEY);
    o2Facebook_->setClientSecret(FB_APP_SECRET);
    o2Facebook_->setLocalPort(localPort);
    o2Facebook_->setRequestUrl(FB_REQUEST_URL);  // Use the desktop login UI

    o2Facebook_->setScope(FB_REQUEST_SCOPE);

    // Create a store object for writing the received tokens
    O0SettingsStore *store = new O0SettingsStore(O2_ENCRYPTION_KEY);
    store->setGroupKey("facebook");
    o2Facebook_->setStore(store);

    connect(o2Facebook_, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(o2Facebook_, SIGNAL(linkingFailed()), this, SIGNAL(linkingFailed()));
    connect(o2Facebook_, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    connect(o2Facebook_, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    connect(o2Facebook_, SIGNAL(closeBrowser()), this, SLOT(onCloseBrowser()));
}

void FBDemo::doOAuth(O2::GrantFlow grantFlowType) {
    qDebug() << "HELLO";
    qDebug() << "Starting OAuth 2 with grant flow type" << GRANTFLOW_STR(grantFlowType) << "...";
    o2Facebook_->setGrantFlow(grantFlowType);
    o2Facebook_->unlink();
    o2Facebook_->link();
}

void FBDemo::validateToken() {
    if (!o2Facebook_->linked()) {
        qWarning() << "ERROR: Application is not linked!";
        emit linkingFailed();
        return;
    }

    QString accessToken = o2Facebook_->token();
    QString debugUrlStr = QString(FB_DEBUG_TOKEN).arg(accessToken);
    QNetworkRequest request = QNetworkRequest(QUrl(debugUrlStr));
    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
    QNetworkReply *reply = mgr->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
    qDebug() << "Validating user token. Please wait...";
}

void FBDemo::onOpenBrowser(const QUrl &url) {
    QDesktopServices::openUrl(url);
}

void FBDemo::onCloseBrowser() {
}

void FBDemo::onLinkedChanged() {
    qDebug() << "Link changed!";
}

void FBDemo::onLinkingSucceeded() {
    O2Facebook *o1t = qobject_cast<O2Facebook *>(sender());
    if (!o1t->linked()) {
        return;
    }
    QVariantMap extraTokens = o1t->extraTokens();
    if (!extraTokens.isEmpty()) {
        emit extraTokensReady(extraTokens);
        qDebug() << "Extra tokens in response:";
        foreach (QString key, extraTokens.keys()) {
            qDebug() << "\t" << key << ":" << (extraTokens.value(key).toString().left(3) + "...");
        }
    }
    getInformation();
    emit linkingSucceeded();
}

void FBDemo::onFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) {
        qWarning() << "NULL reply!";
        emit linkingFailed();
        return;
    }

    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Reply error:" << reply->error();
        qWarning() << "Reason:" << reply->errorString();
        emit linkingFailed();
        return;
    }

    QByteArray replyData = reply->readAll();
    bool valid = !replyData.contains("error");
    if (valid) {
        qDebug() << "Token is valid";
        emit linkingSucceeded();
    } else {
        qDebug() << "Token is invalid";
        emit linkingFailed();
    }
}

void FBDemo::getInformation() {
    o2Facebook_->token();
    QUrl url(FbGraph);
#if QT_VERSION < 0x050000
    url.addQueryItem("access_token", o2Facebook_->token());
#else
    QUrlQuery query(url);
    query.addQueryItem("access_token", o2Facebook_->token());
    url.setQuery(query);
#endif
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyInformation()));

    reply = manager->get(QNetworkRequest(url));

}

void FBDemo::replyInformation()
{
    if(reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        QJsonDocument temp = QJsonDocument::fromJson(strReply.toUtf8());

        response = temp;
        emit replied();

    } else {
        qDebug() << "ERROR";
        emit linkingFailed();
    }
}

QJsonDocument FBDemo::getResponse() {
    return this->response;
}
