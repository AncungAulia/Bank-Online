#include "Admin.h"

Admin::Admin(std::string name, std::string password) 
    : Account(name, password) {}

bool Admin::login(const std::string& inputName, const std::string& inputPassword) {
    return (inputName == name && inputPassword == password);
}