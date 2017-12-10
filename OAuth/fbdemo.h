#ifndef FBDEMO_H
#define FBDEMO_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QMetaEnum>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QUrl>
#if QT_VERSION >= 0x050000
#include <QUrlQuery>
#endif
#include "o2facebook.h"

class FBDemo : public QObject
{
    Q_OBJECT

public:
    explicit FBDemo(QObject *parent = 0);
    void getInformation();
    QJsonDocument getResponse();

signals:
    void extraTokensReady(const QVariantMap &extraTokens);
    void linkingFailed();
    void linkingSucceeded();
    void replied();

public slots:
    void doOAuth(O2::GrantFlow grantFlowType);
    void validateToken();

private slots:
    void onLinkedChanged();
    void onLinkingSucceeded();
    void onOpenBrowser(const QUrl &url);
    void onCloseBrowser();
    void onFinished();

    void replyInformation();

private:
    O2Facebook *o2Facebook_;
    QNetworkReply *reply;
    QJsonDocument response;
};

#endif // FBDEMO_H
