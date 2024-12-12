#include <QApplication>
#include "LoginPage.h"
#include "AdminPanell.h"
#include "UserPanell.h"
#include "DataBase.h"

template <typename CurrentPanelType, typename NewPanelType>
void switchPanel(CurrentPanelType* currentPanel, NewPanelType* newPanel) {
    currentPanel->hide();
    newPanel->show();
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    DataBase db("flight.db");
    LoginPage loginPage;
    AdminPanell adminPanel(&db);
    UserPanell userPanel(&db);
    QObject::connect(&loginPage, &LoginPage::adminLoginSuccessful, [&]() {
        switchPanel(&loginPage, &adminPanel);
    });

    QObject::connect(&loginPage, &LoginPage::userLoginSuccessful, [&]() {
        switchPanel(&loginPage, &userPanel);
    });

    QObject::connect(&adminPanel, &AdminPanell::logoutRequested, [&]() {
        switchPanel(&adminPanel, &loginPage);
    });

    QObject::connect(&userPanel, &UserPanell::logoutRequested, [&]() {
        switchPanel(&userPanel, &loginPage);
    });
    loginPage.show();
    return app.exec();
}
