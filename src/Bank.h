#ifndef BANK_H
#define BANK_H

#include "Client.h"
#include "DBase.h"

class Bank {
private:
    DBase& db;
    
public:
    Bank(DBase& database);
    bool deposit(Client& client, double amount, const std::string& pin);
    bool withdraw(Client& client, double amount, const std::string& pin);
    bool transfer(Client& sender, const std::string& receiverAccount,
                 double amount, const std::string& pin);
};

#endif