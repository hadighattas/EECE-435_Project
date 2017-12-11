/**
 * \file signupmenu.cpp
 * \brief Sign up code linked to the sign up ui
*/
#include "signupmenu.h"
#include "ui_signupmenu.h"


using namespace std;


SignUpMenu::SignUpMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpMenu)
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->confPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->fbSignUp->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(SignUp.png)");
}

SignUpMenu::~SignUpMenu()
{
    delete ui;
}

/**
 * @brief SignUpMenu::setSackedWidget
 * @param stack
 */
void SignUpMenu::setStackedWidget(QStackedWidget *stack){
    this->q=stack;
}

/**
 * @brief SignUpMenu::validateEmail Checks if user email is valid
 * @param email
 * @return true if email is valid or false if it is not valid
 */
bool SignUpMenu::validateEmail(QString email){

QRegularExpression regex("^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$");
if(!regex.match(email).hasMatch())
{
    return false;
}
return true;
}

/**
 * @brief SignUpMenu::on_emailLineEdit_textChanged Calls validate email on email line edit
 * @param arg1
 */
void SignUpMenu::on_emailLineEdit_textChanged(const QString &arg1)
{
    if(!this->validateEmail(arg1)) {
        emailValid = false;
        ui->emailValidateView->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image: url(x.png)");
    }
    else{
        emailValid = true;
        ui->emailValidateView->setStyleSheet("background:transparent;\nborder:0px;\nbackground-image:none");
    }
}

/**
 * @brief SignUpMenu::on_usernameLineEdit_textChanged CHecks if username is available while typing it
 * @param arg1
 */
void SignUpMenu::on_usernameLineEdit_textChanged(const QString &arg1)
{
    if (user.exists("any", ui->usernameLineEdit->text()) && !(ui->usernameLineEdit->text().contains(" "))) {
        ui->message->setText("Username not available");
        userNameValid = false;
    }
    else {
        ui->message->setText("");
        userNameValid = true;
    }
}

/**
 * @brief SignUpMenu::on_signupButton_clicked
 */
void SignUpMenu::on_signupButton_clicked()
{
    /**
      * Check if all fields are filled
    */
    if (ui->firstLineEdit->text().isEmpty() || ui->lastLineEdit->text().isEmpty() || ui->emailLineEdit->text().isEmpty() ||
            ui->usernameLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty() || ui->ageSpinBox->value() == 0 ||
            (!(ui->mRadioButton->isChecked()) && !(ui->fRadioButton->isChecked()))) {
            ui->message->setText("Please fill all the fields");
            return;
        }
    /**
      * Check if email is valid to diplay appropriate message
    */
    if (!emailValid)
        ui->message->setText("Invalid email");
    /**
      * Check if username is valid to diplay appropriate message
    */
    if (!userNameValid)
        ui->message->setText("Username already taken");
    /**
      * Continue if both username and email are valid
    */
    else if (emailValid && userNameValid) {
        QString Gender;
        if (ui->fRadioButton->isChecked())
            Gender = "Female";
        else
            Gender = "Male";
        /**
          * Check if password length is sufficient
        */
        if (ui->passwordLineEdit->text().length() < 6) {
            ui->message->setText("Password too short");
            return;
        }
        /**
          * Check if user is already signed up with email
        */
        if (user.exists(ui->emailLineEdit->text(), ui->usernameLineEdit->text())) {
            ui->message->setText("You already have an account");
            return;
        }
        /**
          * Check if both password and confirm password fields match
        */
        if (ui->passwordLineEdit->text() != ui->confPasswordLineEdit->text()){
            ui->message->setText("Passwords do not match");
            return;
        }
        user.signUp(ui->firstLineEdit->text(), ui->lastLineEdit->text(), ui->emailLineEdit->text(),
                    ui->usernameLineEdit->text(), ui->passwordLineEdit->text(), ui->ageSpinBox->text(),
                    Gender);
        user.login(ui->usernameLineEdit->text(), ui->passwordLineEdit->text());
        theUser = user;
        theUser.addGameScore(1, 1000);
        theUser.addGameScore(3, 900);
        theUser.addGameScore(1, 900);
        MainMenu *mainMenu = new MainMenu;
        mainMenu->setStackedWidget(q);
        q->addWidget(mainMenu);
        q->setCurrentWidget(mainMenu);
        mainIndex = q->indexOf(mainMenu);
        string s="notify-send 'Welcome "+ui->usernameLineEdit->text().toStdString()+"' 'You have successfully signed up.' '-t' 100";
        system(s.c_str());
    }
}

void SignUpMenu::on_backButton_clicked()
{
    q->removeWidget(this);
    WelcomeMenu *welcomemenu=new WelcomeMenu;
    welcomemenu->setStackedWidget(q);
    q->addWidget(welcomemenu);
    q->setCurrentWidget(welcomemenu);
}

/**
 * @brief SignUpMenu::mousePressEvent check if user presses on sign up with facebook
 * @param event
 */
void SignUpMenu::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton && !fbDisabled) {
        QPoint remapped = ui->fbSignUp->mapFromParent( event->pos() );
        if ( ui->fbSignUp->rect().contains( remapped ) )
        {
            fbDisabled = true;
            QCoreApplication::setOrganizationName("MySoft");
            QCoreApplication::setOrganizationDomain("mysoft.com");
            QCoreApplication::setApplicationName("EECE-435_Project");

            QTimer::singleShot(0, &helper, SLOT(processArgs()));
            connect(&helper, SIGNAL(success()), this, SLOT(signUpFB()));
            connect(&helper, SIGNAL(fail()), this, SLOT(fbFailed()));
        }
    }
}

/**
 * @brief SignUpMenu::signUpFB Takes response of the facebook sign up helper and set fields to the information
 */
void SignUpMenu::signUpFB() {

    QJsonObject jObject = helper.getResponse().object();
    qDebug() << jObject;
    ui->usernameLineEdit->setText(jObject["first_name"].toString()+jObject["last_name"].toString());
    ui->emailLineEdit->setText(jObject["email"].toString());
    ui->emailLineEdit->setDisabled(true);
    ui->firstLineEdit->setText(jObject["first_name"].toString());
    ui->firstLineEdit->setDisabled(true);
    ui->lastLineEdit->setText(jObject["last_name"].toString());
    ui->lastLineEdit->setDisabled(true);
    if (jObject["gender"].toString() == "male")
        ui->mRadioButton->setChecked(true);
    else
        ui->fRadioButton->setChecked(true);
    ui->fRadioButton->setDisabled(true);
    ui->mRadioButton->setDisabled(true);
    QString birthday = jObject["birthday"].toString();
    QDate date = QDate::fromString(birthday, "M/dd/yyyy");
    int age = (QDate::currentDate().year() - date.year());
    if (date < QDate::currentDate()) {
        age--;
    }
    ui->ageSpinBox->setValue(age);
    ui->ageSpinBox->setDisabled(true);
    fbDisabled = false;
    ui->signupButton->setStyleSheet("QPushButton:focus { outline-color:white; \nborder:1px solid #ffffff;}\nQPushButton{\nbackground:transparent;\nborder:none;\ncolor:RoyalBlue;\n}\n");
}

/**
 * @brief SignUpMenu::fbFailed Re-enables facebook sign up button after failed sign up
 */
void SignUpMenu::fbFailed() {
    fbDisabled = false;
}

