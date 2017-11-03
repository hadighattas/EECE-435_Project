#include "user.h"

User *user = new User;

User::User()
{
}

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
    users << firstName.toStdString() << '|' << lastName.toStdString() << '|' << email.toStdString()
          << '|' << username.toStdString() << '|' << password.toStdString() << '|' <<
             age.toStdString() << '|' << gender.toStdString() << "\n\n\n\n\n";
    users.close();
}
