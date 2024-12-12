#pragma once
#include "User.h"
#include "FlightManager.h"

class Admin : public User, public FlightManager {

public:
    Admin(const std::string& username);
    void menu() override;
};
