#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"

// subclass dari class Account
class Admin : public Account {
public:
    //constructor dengan default parameter
    Admin(std::string name = "Admin", std::string password = "1234"); 

    //fungsi login yang override dengan fungsi login yang berada di class Account
    bool login(const std::string& inputName, 
               const std::string& inputPassword) override; 
};
#endif