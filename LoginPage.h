#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include "ErrorHandler.h"

class LoginPage : public QWidget {
    Q_OBJECT

public:
    LoginPage(QWidget* parent = nullptr);

signals:
    void adminLoginSuccessful();
    void userLoginSuccessful();

private slots:
    void onLoginClicked();

private:
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QPushButton* loginButton;
    void сheckInputFields();
};

#endif // LOGINPAGE_H
