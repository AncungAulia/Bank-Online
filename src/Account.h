#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    std::string name;
    std::string password;

public:
    Account(std::string name = "", std::string password = "");
    virtual ~Account() = default;
    
    std::string getName() const;
    std::string getPassword() const;
    void setName(const std::string& name);
    void setPassword(const std::string& password);
    
    virtual bool login(const std::string& inputName, const std::string& inputPassword) = 0;
};

#endif