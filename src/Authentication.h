#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "Admin.h"
#include "Client.h"

class Authentication {
private:
    Admin admin;
    
public:
    //constructor
    Authentication();

    //method dari class Authentication

    bool registerClient(const Client& client);
    //menghandle registrasi Client

    Client* loginClient(const std::string& name, 
                        const std::string& password); 
    //menghandle login Client

    Admin* loginAdmin(const std::string& name, 
                      const std::string& password);
    //menghandle login Admin (sudah terdapat default name dan password)
};

#endif