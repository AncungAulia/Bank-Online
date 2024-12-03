#include "Client.h"

Client::Client(std::string name, std::string password, std::string email,
               std::string phone, std::string pin, std::string accountNumber, double balance)
    : Account(name, password), email(email), phone(phone), pin(pin), 
      accountNumber(accountNumber), balance(balance) {}

std::string Client::getEmail() const { return email; }
std::string Client::getPhone() const { return phone; }
std::string Client::getPin() const { return pin; }
std::string Client::getAccountNumber() const { return accountNumber; }
double Client::getBalance() const { return balance; }

void Client::setEmail(const std::string& email) { this->email = email; }
void Client::setPhone(const std::string& phone) { this->phone = phone; }
void Client::setPin(const std::string& pin) { this->pin = pin; }
void Client::setAccountNumber(const std::string& accNum) { this->accountNumber = accNum; }
void Client::setBalance(double balance) { this->balance = balance; }

bool Client::login(const std::string& inputName, const std::string& inputPassword) {
    return (inputName == name && inputPassword == password);
}
