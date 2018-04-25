#include "user.h"

User *user;

User::User(QObject *parent) : QObject(parent)
{

}

void User::storeData(QString firstName, QString lastName, QString email, QString username, QString password, QString age, QString gender) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->username = username;
    this->password = password;
    this->age = age;
    this->gender   = gender;

    fbh->storeUserData(firstName, lastName, email, username, password, age, gender);
}

/**
 * @brief User::signUp Signs up the user and save his information in txt file
 * @param firstName
 * @param lastName
 * @param email
 * @param username
 * @param password
 * @param age
 * @param gender
 * @return
 */
bool User::signUp() {
    connect(fbh, SIGNAL(notifyUserSignup(int)), this, SLOT(firebaseSignupResponse(int)));
    fbh->signUp();
    fbh->getGlobalScores();

    return true;
}

void User::firebaseSignupResponse(int result) {
    emit signupResult(result);
}

/**
 * @brief User::login Logs in the user and loads his information
 * @param username
 * @param password
 * @return
 */

bool User::login(QString email, QString password) {
    qDebug() << "before connect";

    connect(fbh, SIGNAL(loginResult(bool)), this, SLOT(loginResponse(bool)));

    qDebug() << "connect successful";

    this->email = email;
    this->password = password;

    fbh->signIn(email, password);

    return true;
}

void User::loginResponse(bool success) {
    if (success) {
        fbh->getUserData();
        fbh->getGlobalScores();

        QStringList info = fbh->getInfo();
        this->firstName = info[0];
        this->lastName = info[1];
        this->username = info[2];
        this->age = info[3];
        this->gender = info[4];

        emit loginUserResult(true);
    }
    else
        emit loginUserResult(false);

}

/**
 * @brief User::exists Checks if the user exists or username taken
 * @param email If email is "any" then checking if username taken
 * @param username
 * @return
 */
bool User::exists(QString email, QString username) {
    QFile inputFile("users.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList data = line .split("|", QString::SkipEmptyParts);
          if(data.length()>2){
          if (data.at(0) == username || (data.at(2) == email && email != "any")) {
              return true;
          }
          }
       }
    }
    inputFile.close();
    return false;
}

void User::addGameScore(int game, int score) {
    fbh->addScore(game, score);
    fbh->modifyGlobal(game, score);
}

QStringList User::getGame1Scores() {
    QStringList list = fbh->getScore1();
    qDebug() << "game1score:" << list;
    return list;
}

QStringList User::getGame2Scores() {
    QStringList list = fbh->getScore2();

    return list;
}

QStringList User::getGame3Scores() {
    QStringList list = fbh->getScore3();
    return list;
}

int User::averageGlobalScore(int game) {
    return fbh->getGlobalScore(game);
}
