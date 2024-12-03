#ifndef CLIENT_H
#define CLIENT_H

#include "Account.h"

class Client : public Account {
private:
    std::string email;
    std::string phone;
    std::string pin;
    std::string accountNumber;
    double balance;

public:
    Client(std::string name = "", std::string password = "", std::string email = "",
           std::string phone = "", std::string pin = "", std::string accountNumber = "", double balance = 0.0);
    
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getPin() const;
    std::string getAccountNumber() const;
    double getBalance() const;
    
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setPin(const std::string& pin);
    void setAccountNumber(const std::string& accNum);
    void setBalance(double balance);
    
    bool login(const std::string& inputName, const std::string& inputPassword) override;
};

#endif