#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "Admin.h"
#include "Client.h"

class Authentication {
private:
    Admin admin;
    
public:
    Authentication();
    bool registerClient(const Client& client);
    Client* loginClient(const std::string& name, const std::string& password);
    Admin* loginAdmin(const std::string& name, const std::string& password);
};

#endif