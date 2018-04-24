/**
 * \file user.cpp
 * \brief User class that performs operations on user data in txt file
 *
*/
#include "user.h"

User *user = new User;

User::User(){

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

    fbh->signUp();
    fbh->getGlobalScores();

    return true;
}
/**
 * @brief User::login Logs in the user and loads his information
 * @param username
 * @param password
 * @return
 */

bool User::login(QString email, QString password) {
    this->email = email;
    this->password = password;

       fbh->signIn(email, password);
       fbh->getUserData();
       fbh->getGlobalScores();

       QStringList info = fbh->getInfo();
       this->firstName = info[0];
       this->lastName = info[1];
       this->username = info[2];
       this->age = info[3];
       this->gender = info[4];

       return true;
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
