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
    game1Scores.append("game1");
    game2Scores.append("game2");
    game3Scores.append("game3");
    ofstream users;
    users.open("users.txt", ios::app);
    users << username.toStdString() << '|' << password.toStdString() << '|' << email.toStdString()
          << '|' <<  firstName.toStdString() << '|' << lastName.toStdString() << '|' <<
             age.toStdString() << '|' << gender.toStdString() << "\ngame1 \n" << "game2 \n" << "game3 \n";
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
       game1Scores.clear();
       game2Scores.clear();
       game3Scores.clear();
       game1Scores.append("game1");
       game2Scores.append("game2");
       game3Scores.append("game3");
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          char *temp = strtok((char*)(line.toStdString().c_str()), "|");
          if(temp != NULL){
              if(strcmp(temp, username.toStdString().c_str()) == 0) {
                  temp = strtok(NULL, "|");
                  if (strcmp(temp, password.toStdString().c_str()) == 0) {
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
                      for (int i=0; i<3; i++) {
                          line = in.readLine();
                          char *temp = strtok((char*)(line.toStdString().c_str()), " ");
                          temp = strtok(NULL, " ");
                          if(temp != NULL){
                              while(temp != NULL) {
                                  if (i == 0)
                                      game1Scores.append(QString(temp));
                                  else if (i == 1)
                                      game2Scores.append(QString(temp));
                                  else
                                      game3Scores.append(QString(temp));
                                  temp = strtok(NULL, " ");
                              }
                          }
                      }
                      inputFile.close();
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
           inputFile.close();
           return false;
       }
    }
    inputFile.close();
    return true;
}

void User::addGameScore(int game, int score) {
    QStringList currentList;
    QString scoreString = QString::number(score);
    if (game == 1){
        game1Scores.append(scoreString);
        currentList = game1Scores;
    }
    else if (game ==2){
        game2Scores.append(scoreString);
        currentList = game2Scores;
    }
    else {
        game3Scores.append(scoreString);
        currentList = game3Scores;
    }
    QFile inputFile("users.txt");
    QString line;
    QString modifiedLine;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          modifiedLine = in.readLine();
          char *temp = strtok((char*)(modifiedLine.toStdString().c_str()), "|");
          if(temp != NULL){
              if(strcmp(temp, this->username.toStdString().c_str()) == 0) {
                  modifiedLine = in.readLine();
                  if (game > 1)
                      modifiedLine = in.readLine();
                  if (game > 2)
                      modifiedLine = in.readLine();
                  break;
              }
          }
       }
    }
    inputFile.close();
    ofstream temp;
    temp.open("temp.txt");
    QFile inputFile2("users.txt");
    if (inputFile2.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile2);
        while (!in.atEnd())
        {
            line = in.readLine();
            if (line != modifiedLine) {
                temp << line.toStdString() << endl;
            }
            else {
                QString newModifiedLine;
                for (int i = 0; i < currentList.size(); i++) {
                    newModifiedLine.append(currentList.at(i) + " ");
                }
                temp << newModifiedLine.toStdString() << endl;
            }
        }
    }
    inputFile2.close();
    temp.close();
    remove("users.txt");
    rename("temp.txt","users.txt");
}
