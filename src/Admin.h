#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"

class Admin : public Account {
public:
    Admin(std::string name = "Admin", std::string password = "1234");
    bool login(const std::string& inputName, const std::string& inputPassword) override;
};

#endif