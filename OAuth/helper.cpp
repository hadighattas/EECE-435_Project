#include "helper.h"


void Helper::processArgs() {
    connect(&fbdemo_, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(&fbdemo_, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    fbdemo_.doOAuth(O2::GrantFlowAuthorizationCode);

}

void Helper::onLinkingFailed() {
    emit fail();
}

void Helper::onLinkingSucceeded() {
    connect(&fbdemo_, SIGNAL(replied()), this, SLOT(validate()));
}

QJsonDocument Helper::getResponse() {
    return fbdemo_.getResponse();
}

void Helper::validate() {
    emit success();
}
