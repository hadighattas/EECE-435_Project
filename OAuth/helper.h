#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QStringList>
#include <QTimer>
#include <QDebug>

#include "fbdemo.h"

const char OPT_OAUTH_CODE[] = "-o";
const char OPT_VALIDATE_TOKEN[] = "-v";

const char USAGE[] = "\n"
                     "Usage: facebookdemo [OPTION]...\n"
                     "Get OAuth2 access tokens from Facebook's OAuth service\n"
                     "\nOptions:\n"
                     "  %1\t\tLink with Facebook OAuth2 service using Authorization Code\n"
                     "  %2\t\tValidate Access Token\n";

class Helper : public QObject
{
    Q_OBJECT
public:
    Helper() : QObject(), fbdemo_(this), waitForMsg_(false), msg_(QString()) {}
    QJsonDocument getResponse();

signals:
    void success();
    void fail();

public slots:
    void processArgs();
    void onLinkingFailed();
    void onLinkingSucceeded();
    void validate();

private:
    FBDemo fbdemo_;
    bool waitForMsg_;
    QString msg_;

};

#endif // HELPER_H
