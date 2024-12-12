#include "LoginPage.h"
#include <QMessageBox>


LoginPage::LoginPage(QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("Login");

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Username");

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);
    loginButton->setEnabled(false); // Изначально кнопка отключена

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginPage::onLoginClicked);
    connect(usernameLineEdit, &QLineEdit::textChanged, this, &LoginPage::сheckInputFields);
    connect(passwordLineEdit, &QLineEdit::textChanged, this, &LoginPage::сheckInputFields);
}


void LoginPage::onLoginClicked() {
    try {
        QString username = usernameLineEdit->text();
        QString password = passwordLineEdit->text();

        if (username == "admin" && password == "admin") {
            emit adminLoginSuccessful();
        } else if (username == "user" && password == "user") {
            emit userLoginSuccessful();
        } else {
            throw std::runtime_error("Invalid username or password.");
        }
    } catch (const std::exception& e) {
        ErrorHandler::handleException(e);
    } catch (...) {
        ErrorHandler::handleUnknownException();
    }
}

void LoginPage::сheckInputFields() {
    bool isUsernameEmpty = usernameLineEdit->text().trimmed().isEmpty();
    bool isPasswordEmpty = passwordLineEdit->text().trimmed().isEmpty();
    loginButton->setEnabled(!isUsernameEmpty && !isPasswordEmpty);
}
