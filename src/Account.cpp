#include "Account.h"

Account::Account(std::string name, std::string password) 
    : name(name), password(password) {}

std::string Account::getName() const { return name; }
std::string Account::getPassword() const { return password; }
void Account::setName(const std::string& name) { this->name = name; }
void Account::setPassword(const std::string& password) { this->password = password; }
