#ifndef CLIENT_H
#define CLIENT_H

#include "Account.h"

// Subclass dari class Account
class Client : public Account {
private:
    // Atribut dari class Client
    std::string email;
    std::string phone;
    std::string pin;
    std::string accountNumber;
    double balance;

public:
    /*Constructor dengan default parameter untuk balance berupa 0.0, 
    karena akun pertama kali dibentuk dengan saldo 0 rupiah*/
    Client(std::string name = "",
           std::string password = "", std::string email = "",
           std::string phone = "", std::string pin = "", std::string accountNumber = "", double balance = 0.0);
    
    //getter
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getPin() const;
    std::string getAccountNumber() const;
    double getBalance() const;
    
    //setter
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setPin(const std::string& pin);
    void setAccountNumber(const std::string& accNum);
    void setBalance(double balance);
    
    //fungsi login yang override dengan fungsi login yang berada di class Account
    bool login(const std::string& inputName, const std::string& inputPassword) override;  
};

#endif