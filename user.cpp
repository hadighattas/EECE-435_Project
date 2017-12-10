/**
 * \file user.cpp
 * \brief User class that performs operations on user data in txt file
 *
*/
#include "user.h"

User *user = new User;

User::User(){

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
bool User::signUp(QString firstName, QString lastName, QString email, QString username,
                  QString password, QString age, QString gender) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->username = username;
    this->password = password;
    this->age = age;
    this->gender = gender;

    ofstream users;
    users.open("users.txt", ios::app);
    users << username.toStdString() << '|' << password.toStdString() << '|' << email.toStdString()
          << '|' <<  firstName.toStdString() << '|' << lastName.toStdString() << '|' <<
             age.toStdString() << '|' << gender.toStdString() << "\n\n\n\n\n";
    users.close();
    return true;
}
/**
 * @brief User::login Logs in the user and loads his information
 * @param username
 * @param password
 * @return
 */

bool User::login(QString username, QString password) {
    QFile inputFile("users.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          char *temp = strtok((char*)(line.toStdString().c_str()), "|");
          if(temp != NULL){
              if(strcmp(temp, username.toStdString().c_str()) == 0) {
                  temp = strtok(NULL, "|");
                  if (strcmp(temp, password.toStdString().c_str()) == 0) {
                      inputFile.close();
                      this->username = username;
                      this->password = password;
                      int count = 0;
                      while(temp != NULL) {
                          temp = strtok(NULL, "|");
                          switch(count) {
                              case 0:
                                  this->email = QString(temp);
                              case 1:
                                  this->firstName = QString(temp);
                              case 2:
                                  this->lastName = QString(temp);
                              case 3:
                                  this->age = QString(temp);
                              case 4:
                                  this->gender = QString(temp);
                          }
                          count++;
                      }
                      return true;
                  }
              }
          }
       }
       inputFile.close();
    }
    return false;
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
          char *temp = strtok((char*)(line.toStdString().c_str()), "|");
          if(temp != NULL){
              if(strcmp(temp, username.toStdString().c_str()) != 0) {
                  temp = strtok(NULL, "|");
                  temp = strtok(NULL, "|");
                  if (strcmp(temp, email.toStdString().c_str()) == 0 && email != "any")
                    break;
              }
              else break;

          }
       }
       if (in.atEnd()){
           return false;
       }
    }
    return true;
}
