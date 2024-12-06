#include "DBase.h"
#include "Utility.h"
#include <fstream>
#include <sstream>
#include <iomanip>

bool DBase::saveClient(const Client& client) {
    std::ofstream file(CLIENT_FILE, std::ios::app);
    if (!file) return false;

    file << client.getName() << "|"
         << client.getPassword() << "|"
         << client.getEmail() << "|"
         << client.getPhone() << "|"
         << client.getPin() << "|"
         << client.getAccountNumber() << "|"
         << std::fixed << std::setprecision(2) << client.getBalance() << "\n";
    
    return true;
}

bool DBase::updateClient(const Client& client) {
    std::vector<Client> clients = getAllClients();
    std::ofstream file(CLIENT_FILE);
    if (!file) return false;
    
    for (const auto& c : clients) {
        if (c.getAccountNumber() == client.getAccountNumber()) {
            file << client.getName() << "|"
                 << client.getPassword() << "|"
                 << client.getEmail() << "|"
                 << client.getPhone() << "|"
                 << client.getPin() << "|"
                 << client.getAccountNumber() << "|"
                 << std::fixed << std::setprecision(2) << client.getBalance() << "\n";
        } else {
            file << c.getName() << "|"
                 << c.getPassword() << "|"
                 << c.getEmail() << "|"
                 << c.getPhone() << "|"
                 << c.getPin() << "|"
                 << c.getAccountNumber() << "|"
                 << std::fixed << std::setprecision(2) << c.getBalance() << "\n";
        }
    }
    return true;
}

bool DBase::deleteClient(const std::string& accountNumber) {
    std::vector<Client> clients = getAllClients();
    std::ofstream file(CLIENT_FILE);
    if (!file) return false;
    
    for (const auto& client : clients) {
        if (client.getAccountNumber() != accountNumber) {
            file << client.getName() << "|"
                 << client.getPassword() << "|"
                 << client.getEmail() << "|"
                 << client.getPhone() << "|"
                 << client.getPin() << "|"
                 << client.getAccountNumber() << "|"
                 << client.getBalance() << "\n";
        }
    }
    std::string transFileName = TRANSACTION_PREFIX + accountNumber + ".txt";
    remove(transFileName.c_str());
    
    return true;
}

std::vector<Client> DBase::getAllClients() {
    std::vector<Client> clients;
    std::ifstream file(CLIENT_FILE);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, password, email, phone, pin, accNum;
        double balance;
        
        std::getline(ss, name, '|');
        std::getline(ss, password, '|');
        std::getline(ss, email, '|');
        std::getline(ss, phone, '|');
        std::getline(ss, pin, '|');
        std::getline(ss, accNum, '|');
        ss >> balance;
        
        clients.emplace_back(name, password, email, phone, pin, accNum, balance);
    }
    
    return clients;
}

Client DBase::getClientByAccountNumber(const std::string& accountNumber) {
    std::vector<Client> clients = getAllClients();
    for (const auto& client : clients) {
        if (client.getAccountNumber() == accountNumber) {
            return client;
        }
    }
    return Client();
}

void DBase::saveTransaction(const std::string& accountNumber, const std::string& type,
                          double amount, const std::string& targetAccount) {
    std::string filename = TRANSACTION_PREFIX + accountNumber + ".txt";
    std::ofstream file(filename, std::ios::app);
    
    if (file) {
        file << Utility::getCurrentDateTime() << "|"
             << type << "|"
             << std::fixed << std::setprecision(2) << amount << "|"
             << targetAccount << "\n";
    }
}

std::vector<std::string> DBase::getTransactionHistory(const std::string& accountNumber) {
    std::vector<std::string> history;
    std::string filename = TRANSACTION_PREFIX + accountNumber + ".txt";
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        history.push_back(line);
    }
    
    return history;
}
